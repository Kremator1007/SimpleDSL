#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include "for_each_on_tuple.h"
#include "trim.h"
template <typename T>
struct type_identity {
	using type = T;
};

struct Command {
	virtual bool tryParsingParameters(std::string commandLine) = 0;
	virtual void parseAndRun(std::string commandLine) = 0;
	virtual std::string stringRepr() = 0;
	virtual ~Command() = default;
};

template <typename... Ts>
struct CommandImpl : public Command {
	CommandImpl(std::string commandName, std::function<void(Ts...)> callable)
	    : commandName(commandName), commandCallable(callable) {}
	std::string commandName;
	std::function<void(Ts...)> commandCallable;
	std::tuple<Ts...> inputParameters;
	void parseAndRun(std::string commandLine) override {
		std::stringstream lineStream(commandLine);
		std::string commandNameOnInput;
		lineStream >> commandNameOnInput;
		assert(commandNameOnInput == commandName);
		forEachOnTuple(inputParameters,
		               [&](auto& tupleElem) { lineStream >> tupleElem; });
		std::apply(commandCallable, inputParameters);
	}
	bool tryParsingParameters(std::string commandLine) override {
		bool parsingSuccess = true;
		std::stringstream lineStream(commandLine);
		std::string commandNameOnInput;
		lineStream >> commandNameOnInput;
		if (commandNameOnInput != commandName) parsingSuccess = false;
		forEachOnTuple(inputParameters, [&](auto& tupleElem) {
			lineStream >> tupleElem;
			if (lineStream.fail()) parsingSuccess = false;
		});
		std::string remaining;
		getline(lineStream, remaining);
		auto isSpace = [](char ch) { return ch == ' '; };
		if (!std::all_of(remaining.begin(), remaining.end(), isSpace))
			parsingSuccess = false;
		return parsingSuccess;
	}
	std::string stringRepr() override {
		std::string repr = commandName;
		repr = repr + " " + ((std::string((typeid(Ts).name())) + " ") + ...);
		return repr;
	}
};

struct Interpreter {
	std::vector<std::unique_ptr<Command>> commands;
	template <typename... Ts>
	void addCommand(
	    std::string commandName,
	    typename type_identity<std::function<void(Ts...)>>::type callable) {
		commands.emplace_back(new CommandImpl<Ts...>(commandName, callable));
	}
	void runCommand(std::string commandLine) {
		commandLine = trim(commandLine);
		std::vector<std::unique_ptr<Command>*> possibleCandidates;
		for (auto& command : commands) {
			if (command->tryParsingParameters(commandLine))
				possibleCandidates.push_back(&command);
		}
		if (possibleCandidates.size() > 1) {
			std::string ambiguousCallMessage{
			    "Ambiguous function call. Possible candidates are:\n"};
			for (auto commandPtr : possibleCandidates)
				ambiguousCallMessage += ((*commandPtr)->stringRepr() + "\n");
			throw std::runtime_error(ambiguousCallMessage);
		} else if (possibleCandidates.empty()) {
			throw std::runtime_error(
			    "No candidate functions registered for command \"" +
			    commandLine + "\"");
		} else {
			(*possibleCandidates[0])->parseAndRun(commandLine);
		}
	}
};
