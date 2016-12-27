#pragma once
#include <memory>
template<typename T>

class CMyStack
{
	struct Node
	{
		Node(const T &value, const std::shared_ptr<Node> &next)
			: value(value)
			, next(next)
		{
		};	
		T value;
		std::shared_ptr<Node> next;
	};

public:
	CMyStack()
		: s_top(nullptr)
		, s_size(0)
	{
	};
	CMyStack(const CMyStack &other)
	{
		std::shared_ptr<Node> tmp = other.s_top;
		std::shared_ptr<Node> end = std::make_shared<Node>(tmp->value, nullptr);
		s_top = end;

		tmp = tmp->next;
		while (tmp != nullptr)
		{
			end->next = std::make_shared<Node>(tmp->value, nullptr);
			end = end->next;

			tmp = tmp->next;
		}
		s_size = other.GetSize();
	};
	CMyStack(CMyStack &&other)
		: s_top(other.s_top)
		, s_size(other.s_size)
	{
		other.s_top = nullptr;
		other.s_size = 0;
	};

	void Push(const T &element)
	{
		s_top = std::make_shared<Node>(element, s_top);
		++s_size;
	};

	void Pop()
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}
		s_top = s_top->next;
		--s_size;
	};

	T GetElement() const
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}
		return s_top->value;
	};

	size_t GetStackSize()
	{
		return s_size;
	};

	bool IsStackEmpty()
	{
		return s_size == 0;
	};

	void Clear()
	{
		while (s_top -> nullptr)
		{
			s_top =s_top->next;
		}
		s_size = 0;
	};

	CMyStack& operator=(const CMyStack &assigns_stack)
	{
		if (std::addressof(assigns_stack) != this)
		{
			std::shared_ptr<Node> tmp = assigns_stack.s_top;
			std::shared_ptr<Node> end = std::make_shared<Node>(tmp->value, nullptr);
			s_top = end;
			tmp = tmp->next;
			while (tmp != nullptr)
			{
				end->next = std::make_shared<Node>(tmp->value, nullptr);
				end = end->next;
				tmp = tmp->next;
			}
			s_size = assigns_stack.GetSize();
		}
		return *this;
	};

	CMyStack& operator=(CMyStack &&	copied_stack)
	{
		if (std::addressof(copied_stack) != this)
		{
			m_top = copied_stack.m_top;
			m_size = copied_stack.m_size;
			copied_stack.m_top = nullptr;
			copied_stack.m_size = 0;
		}
		return *this;
	};

private:
	std::shared_ptr<Node> m_top;
	size_t m_size;
};
