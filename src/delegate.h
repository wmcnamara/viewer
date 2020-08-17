#pragma once
#ifndef DELEGATE_H
#define DELEGATE_H

#include <vector>
#include <functional>

/*
//Weston McNamara 2020
//Licensed Under MIT https://mit-license.org/
//https://github.com/wmcnamara/delegate
 
//Delegate is a single header, lightweight and easy to use abstraction for storing functions and callbacks.
*/
namespace Events 
{
	class Connection
	{
	public:
		Connection(int index) : m_index(index) {}
		int Index() const { return m_index; }
	private:
		const int m_index;
	};

	template<typename T>
	class Delegate
	{
	public:
		//Invokes each function added to this delegate. 
		//If no handlers exist, it returns false.
		bool Invoke(T param)
		{
			if (m_handlers.empty()) { return false; }

			for (auto handler : m_handlers)
			{
				handler(param);
			}
			return true;
		}

		//Adds a single function to the delegate.
		Connection&& AddHandler(std::function<void(T param)> func)
		{
			//The new function was just added, size will be the position of it.
			m_handlers.push_back(func);

			//Size does not take the index into account, so we subtract one to give the index.
			return Connection(m_handlers.size() - 1);
		}

		//Removes a single function from the delegate
		void RemoveHandler(Connection& conn) { m_handlers.erase(m_handlers.begin() + conn.Index()); }
		void RemoveAllHandlers() { m_handlers.clear(); }

		//Invokes each handler added to this delegate.
		void operator() (T param) { Invoke(param); }

	private:
		std::vector<std::function<void(T param)>> m_handlers;
	};
}
#endif