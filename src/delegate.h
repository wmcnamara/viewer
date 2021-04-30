/*
//Weston McNamara 2020
//Licensed Under MIT https://mit-license.org/
//https://github.com/wmcnamara/delegate
//Delegate is a single header, lightweight and easy to use abstraction for storing functions and callbacks.
//When you call AddHandler, a integer type containing the ID is returned. To call RemoveHandler, you must pass this integer.
//If you know you might delete the handler you add, be sure to keep track of this number.
//Uses std::map to represent ID/Function data.
//Removing a handler of ID 0 simply returns, and does nothing.
*/

#ifndef DELEGATE_INCLUDE
#define DELEGATE_INCLUDE

#include <functional>
#include <map>

template<typename ... T>
class Delegate
{
private:
	typedef std::function<void(T...)> Func_T;
public:
	//Invokes each function added to this delegate. 
	void Invoke(T... param)
	{
		if (m_handlers.empty())
			return;

		for (const auto& key : m_handlers)
		{
			key.second(param...); //Invoke the function
		}
	}

	//Adds a single function to the delegate.
	int AddHandler(Func_T func)
	{
		static int nextID = 1;
		m_handlers.insert(std::pair<int, Func_T>(nextID, func));

		//Return the ID, and increment it.
		return nextID++;
	}

	//Removes a single function from the delegate.
	void RemoveHandler(int ID)
	{
		if (ID == 0)
			return

			m_handlers.erase(ID);
	}

	void RemoveAllHandlers()
	{
		m_handlers.clear();
	}

private:
	std::map<int, Func_T> m_handlers;
};

//Template specialization for no parameter
template<>
class Delegate<void>
{
private:
	typedef std::function<void()> Func_T;
public:
	//Invokes each function added to this delegate. 
	void Invoke()
	{
		if (m_handlers.empty())
			return;

		for (const auto& key : m_handlers)
		{
			key.second(); //Invoke the function
		}
	}

	//Adds a single function to the delegate.
	int AddHandler(Func_T func)
	{
		static int nextID = 1;
		m_handlers.insert(std::pair<int, Func_T>(nextID, func));

		//Return the ID, and increment it.
		return nextID++;
	}

	//Removes a single function from the delegate
	void RemoveHandler(int ID)
	{
		if (ID == 0)
			return;

		m_handlers.erase(ID);
	}

	void RemoveAllHandlers()
	{
		m_handlers.clear();
	}

private:
	std::map<int, Func_T> m_handlers;
};
#endif //DELEGATE_INCLUDE