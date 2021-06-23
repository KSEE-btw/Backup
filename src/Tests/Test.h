#pragma once
#include <string>
#include <vector>
#include"functional"
namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}
		virtual void OnUpdate(float DeltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	};
	class TestMenu : public Test
	{
	public:

		TestMenu(Test*& Test);
		~TestMenu();
		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		template <class T>
		void RegisterTest(std::string name);
	private:
		std::vector< std::pair< std::string, std::function<test::Test*()>>> m_Tests;
		Test*& m_CurrentTest;
	};
	template<class T>
	inline void TestMenu::RegisterTest(std::string name)
	{
		m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
	}
}
