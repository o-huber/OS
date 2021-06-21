#include <iostream>
#include <future>
#include <iomanip>
#include <thread>

using namespace std;
bool exitFlag = false;

int f(int x)
{
	if (x % 2 == 0) return 1;
	else return 0;
}

int g(int x)
{
	if (x == 0)
	{
		while (!exitFlag)
			++x;
		return x;
	}
	else return x;
}


int main(int argc, const char* argv[])
{
	using namespace chrono_literals;
	cout << "Enter x: ";
	int x{};
	cin >> x;
	packaged_task<int(int)> fTask(f);           //The class template std::packaged_task wraps any Callable target
	packaged_task<int(int)> gTask(g);			//(function, lambda expression, bind expression, or another function object) so that it can be invoked asynchronously.
												//Its return value or exception thrown is stored in a shared state which can be accessed through std::future objects.
										//packaged_task can be moved to other threads.

	future_status stF, stG;				//Specifies state of a future as returned by wait_for function of std::future.
	future<int> fFuture = fTask.get_future();
	future<int> gFuture = gTask.get_future();
	thread fThread(move(fTask), x);    //future отримано перед move. Отже, навіть якщо цей крок залишив ftask у невизначеному стані, майбутнє, яке отримає результат виклику  уже отримано.
	thread gThread(move(gTask), x);
	bool flag = true;
	bool flagF = true;
	bool flagFgot = false;
	do
	{
		if(flagFgot ==false)stF = fFuture.wait_for(5s);
		stG = gFuture.wait_for(5s);
		if (flagFgot==false && stF == future_status::ready) {
			flagFgot = true;
			if (!fFuture.get()) {
				cout << "f(x) && g(x)" << '\n';
				cout << "Result: " << false << '\n';
				flagF = false;
				break;
			}
		}
		if (stF == future_status::timeout || stG == future_status::timeout) //the shared state did not become ready before specified timeout duration has passed
		{
		  while (flag){
					cout << "Timeout! Do you want to continue waiting?\n";
					cout << "Enter 'yes' to continue waiting\nEnter 'no' to terminate\nEnter '0' to continue and not asking again \n";
					string command;
					cin >> command;
					if (command == "yes")
					{
						cout << "Continue waiting for 5s\n";
						break;
					}
					else if (command == "no")
					{
						cout << "Terminating\n";
						exitFlag = true;
						fThread.join();  //The function returns when the thread execution has completed
						gThread.join();
						return 0;
					}
					else if (command == "0")
					{
						cout << "Waiting\n";
						flag = false;
						break;
					}
					else
					{
						cout << "Wrong command, try again\n";
						continue;
					}
		  }
		}
		
	}
		while (stF != future_status::ready || stG != future_status::ready);
		
		if (stG == future_status::ready && flagF==true) {
			cout << "f(x) && g(x)" << '\n';
			cout << "Result: " << (true && gFuture.get()) << '\n';
		}
		fThread.join();
		gThread.join();
		return 0;
	
}