#include <iostream> /**/
#include <unistd.h>			// read
#include <functional>		// function , bind
// #include <sys/types.h>
#include <sys/socket.h>

#include "server.hpp"
#include "reactor.hpp"
// #include "reactor_select.hpp"

using namespace ilrd;

using std::cout;
using std::cin;
using std::cout;
using std::endl;

static const int STDIN = 0;

static int Test_init();
static int Test_stdin();
static int Test_tcp();
static int Test_tcp_stdin();

template <typename T>
static void PrintErrorDetails(const char *func, T result, T correct_result, int line_NUM)
{
	cout<< "Func: "<<func<<". result is "<<result<<" and should be: "<<correct_result<<". Line num: "<< line_NUM<<endl;

	return;
}

/*********************************************************************/
int main()
{
	int func_errors = 0;

	int start_count = __LINE__;
	// func_errors += Test_init();
	// func_errors += Test_stdin();
	// func_errors += Test_tcp();
	func_errors += Test_tcp_stdin();
	int end_count = __LINE__;
	
	int total_test_num = end_count - start_count - 1;
	
	int passed_test = total_test_num - func_errors;
	
	if (func_errors == total_test_num)
	{
		cout<< func_errors <<" function/s with error/s"<<endl;
		cout<<"ALL BAD, failed "<<func_errors<< "/" << total_test_num <<" tests" << std::endl;
	}
	else if (func_errors > 0)
	{
		cout<< func_errors <<" function/s with error/s"<<endl;
		cout<<"NOT SO GOOD, passed "<<passed_test<< "/" << total_test_num <<" tests" << std::endl;
	}
	else
	{
		cout<<"ALL GOOD, passed "<<passed_test<< "/" << total_test_num <<" tests" << std::endl;
//		sleep(1);
//		cout<<"Segmentation fault (core dumped)"<<endl;
	}

	return (0);
}
/*********************************************************************/
static int Test_init()
{
	int errors = 0;

	Reactor<ReactorSelect> rec_sec;

	return (errors > 0);
}

/*********************************************************************/
char buff1[10];
std::string check;
void func_stdin(int fd)
{
	read(fd, buff1, 10);
	cout<<buff1<<endl;
	check = buff1;
	
}
static int Test_stdin()
{
	int errors = 0;
	const char * func = "Test_stdin";
	std::function<void(int)> func_temp = func_stdin;
	Reactor<ReactorSelect> rec_sec;
	rec_sec.add(STDIN, func_temp);
	cout<<"waiting for char pressing + enter"<<endl;
	rec_sec.run();
	if (buff1[0] != check[0])
	{
		PrintErrorDetails(func, buff1[0], '\0', __LINE__);
		++errors;		
	}
	return (errors > 0);
}
/*********************************************************************/
static int Test_tcp()
{
	
	int errors = 0;
	// const char * func = "Test_tcp";

	int fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd_socket  == -1)
	{
		perror("socket");
		exit(1);
	}

	Reactor<ReactorSelect> rec_sec;
	Server s(fd_socket, rec_sec, 5002);
	
	rec_sec.add(fd_socket, std::bind(&Server::add_client, s, _1));

	cout<<"waiting for new connection"<<endl;
	while (1)
	{
		rec_sec.run();
	}

	return (errors > 0);	
}
/*********************************************************************/
static int Test_tcp_stdin()
{
	
	int errors = 0;
	// const char * func = "Test_tcp";

	int fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd_socket  == -1)
	{
		perror("socket");
		exit(1);
	}

	Reactor<ReactorSelect> rec_sec;
	Server s(fd_socket, rec_sec, 5003);
	
	rec_sec.add(STDIN, func_stdin);
	rec_sec.add(fd_socket, std::bind(&Server::add_client, s, _1));
	cout<<"waiting for new connection"<<endl<<endl;
	cout<<"waiting for char pressing + enter"<<endl;
	while (1)
	{
		rec_sec.run();
	}

	return (errors > 0);	
}
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/
