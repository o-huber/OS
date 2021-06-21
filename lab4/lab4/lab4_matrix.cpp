/*#include <iostream>
#include <random>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

int N = 100;
int times = 1;
int thread_num = 4;

void printMatrix(vector<vector<int>> a) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

vector<vector<int>> RandomInit(vector<vector<int>>& a) {
	srand(unsigned(clock()));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = rand() / (int)1000;
		}
	}
	return a;
}

vector<vector<int>> DummyInitA(vector<vector<int>>& a) {
	int counter = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			counter++;
			a[i][j] = counter;
		}
	}
	return a;
}

vector<vector<int>> DummyInitB(vector<vector<int>>& b) {
	int counter = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			counter++;
			b[i][j] = N * N + 1 - counter;
		}
	}
	return b;
}

void MultiplyVector(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c, int i, int j) {
	// multiply i row of a on j column of b
	int s = 0;
	for (int k = 0; k < N; k++) {
		s += a[i][k] * b[k][j];
	}
	//printf("Calculated c[%d][%d]: %d\n", i, j, s);
	c[i][j] = s;
}

vector<vector<int>> SerialMultiply(vector<vector<int>> a, vector<vector<int>> b) {
	vector<vector<int>> c(N);
	for (int i = 0; i < N; i++) {
		c[i] = vector<int>(N);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MultiplyVector(a, b, c, i, j);
		}
	}
	return c;
}

vector<vector<int>> MultithreadedN(vector<vector<int>> a, vector<vector<int>> b) {
	vector<vector<int>> c(N);
	for (int i = 0; i < N; i++) {
		c[i] = vector<int>(N);
	}
	vector<vector<thread>> threads(N);
	for (int i = 0; i < N; i++) {
		threads[i] = vector<thread>(N);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			threads[i][j] = thread(MultiplyVector, ref(a), ref(b), ref(c), i, j);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			threads[i][j].join();
		}
	}
	return c;
}

void MatrixPart(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c,
	vector<int> is, vector<int> js) {
	for (int i = 0; i < is.size(); i++) {
		MultiplyVector(ref(a), ref(b), ref(c), is[i], js[i]);
	}
}

vector<vector<int>> MultithreadedNum(vector<vector<int>> a, vector<vector<int>> b) {
	vector<vector<int>> c(N);
	for (int i = 0; i < N; i++) {
		c[i] = vector<int>(N);
	}
	int counter = 0;
	vector<vector<int>> is(thread_num);
	vector<vector<int>> js(thread_num);
	for (int i = 0; i < thread_num; i++) {
		is[i] = vector<int>{};
		js[i] = vector<int>{};
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int thr = counter % thread_num;
			is[thr].push_back(i);
			js[thr].push_back(j);
			counter++;
		}
	}

	vector<thread> threads(thread_num);
	for (int i = 0; i < thread_num; i++) {
		threads[i] = thread(MatrixPart, ref(a), ref(b), ref(c), is[i], js[i]);
	}
	for (int i = 0; i < thread_num; i++) {
		threads[i].join();
	}
	return c;
}

int main() {
	vector<vector<int>> a(N);
	vector<vector<int>> b(N);

	for (int i = 0; i < N; i++) {
		a[i] = vector<int>(N);
		b[i] = vector<int>(N);
	}
	DummyInitA(a);
	DummyInitB(b);
	//cout << "Matrix A=" << endl;
	//printMatrix(a);
	//cout << "Matrix B=" << endl;
	//printMatrix(b);
	vector<vector<int>> c(N);
	auto start = chrono::system_clock::now();
	c = SerialMultiply(a, b);
	auto finish = std::chrono::system_clock::now();
	//cout << "Matrix C=" << endl;
	//printMatrix(c);
	cout << "Serial multiplication time: " << duration_cast<chrono::milliseconds>(finish - start).count() << " ms" << endl;
	vector<vector<int>> c1(N);
	auto start1 = chrono::system_clock::now();
	for (int k = 0; k < times; k++) {
		c1 = MultithreadedN(a, b);
	}
	auto finish1 = std::chrono::system_clock::now();
	//cout << "Matrix C=" << endl;
	//printMatrix(c1);
	cout << "Multi-threaded multiplication time (N): " << duration_cast<chrono::milliseconds>(finish1 - start1).count() << " ms" << endl;
	vector<vector<int>> c2(N);
	auto start2 = chrono::system_clock::now();
	for (int k = 0; k < times; k++) {
		c2 = MultithreadedNum(a, b);
	}
	auto finish2 = std::chrono::system_clock::now();
	//cout << "Matrix C=" << endl;
	//printMatrix(c2);
	cout << "Multi-threaded multiplication time (treadNum): " << duration_cast<chrono::milliseconds>(finish2 - start2).count() << " ms" << endl;
	return 0;
}*/