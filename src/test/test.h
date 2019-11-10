#ifndef TINYSTL_TEST_H_
#define TINYSTL_TEST_H_

#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

namespace tinystl
{
namespace test
{
    #define green redbud::io::state::manual << redbud::io::hfg::green
    #define red   redbud::io::state::manual << redbud::io::hfg::red

    #if defined(_MSC_VER)
    #pragma warning(disable : 4244)
    #pragma warning(disable : 4996)
    #endif
}

namespace test
{
    //单个测试案例的信息
    class TestCase
    {
    public:
        TestCase(const char *case_name) : testcase_name(case_name) {}
        
        //执行测试案例的方法
        virtual void Run() = 0;
    public:
        const char *testcase_name;      //测试案例的名字
        int         nTestResult;        //测试案例的执行结果
        double      nFailed;            //测试失败的案例数
        double      nPassed;            //测试通过的案例数
    };

    //UnitTest 类
    //单元测试，把所有测试案例加入vector中，依次执行测试案例
    class UnitTest
    {
    public:
        static UnitTest *GetInstance(); //获取单例

        TestCase *RegisterTestCase(TestCase *testcase);//注册测试案例

        int Run(); //执行单元测试

        TestCase *CurrentTestCase; //记录当前执行的测试案例
        int nTestResult;//总的执行结果
        int nPassed;    //通过案例数
        int nFailed;    //失败案例数
    protected:
        std::vector<TestCase*> testcases_; //案例集合
    };

    UnitTest* UnitTest::GetInstance()
    {
        static UnitTest instance;
        return &instance;
    }

    TestCase* UnitTest::RegisterTestCase(TestCase *testcase)
    {
        testcases_.push_back(testcase);
        return testcase;
    }

    int UnitTest::Run()
    {
        nTestResult = 1;
        for (std::vector<TestCase*>::iterator it = testcases_.begin(); it != testcases_.end(); ++it)
        {
            TestCase *testacse = *it;
            CurrentTestCase = testacse;
            std::cout << green << "======================================" << std::endl;
            std::cout << green << "Run TestCase:" << testacse->testcase_name << std::endl;
            testacse->Run();
            std::cout << green << "End TestCase:" << testcase->testcase_name << std::endl;
            if (testcase->nTestResult)
            {
                nPassed++;
            }
            else
            {
                nFailed++;
                nTestResult = 0;
            }
        }

        std::cout << green << "======================================" << std::endl;
        std::cout << green << "Total TestCase : " << nPassed + nFailed << std::endl;
        std::cout << green << "Passed : " << nPassed << std::endl;
        std::cout << red << "Failed : " << nFailed << std::endl;
        return nTestResult;
    }

    #define TESTCASE_NAME(testcase_name) \
        testcase_name##_TEST

    #define NANCY_TEST_(testcase_name)                              \ 
    class TESTCASE_NAME(testcase_name) : public TestCasse           \    
    {                                                               \
    public:                                                         \
        TESTCASE_NAME(testcase_name)(const char *case_name)         \
            : TestCasse (case_name) {};                             \
        virtual void Run();                                         \
    private:                                                        \
        static TestCase *const testcase_;                           \
    };                                                              \
                                                                    \
    TestCase* const TESTCASE_NAME(testcase_name)                    \
        ::testcase_ = UnitTest::GetInstance()->RegisterTestCasse(   \
            new TESTCASE_NAME(testcase_name)(#testcase_name));      \
                                                        
    
}
}

#endif