#include "Matrix.h"
#include "AutoVectorized.h"
#include "NotVectorized.h"
#include "SSE.h"

int main() {
	srand(time(0));
	using namespace std::chrono;
	AutoVectorized<float> autoVectorizedService = AutoVectorized<float>();
	NotVectorized<float> notVectorizedService = NotVectorized<float>();
	SSE<float> sse = SSE<float>();

	Matrix<float> a = Matrix<float>(110, 110, 4, 2);
	Matrix<float> b = Matrix<float>(110, 110, 2, 4);
	Matrix<float>* c = new Matrix<float>(a.lines, b.columns, a.includedLines, b.includedColumns);
	Matrix<float>* d = new Matrix<float>(a.lines, b.columns, a.includedLines, b.includedColumns);
	a.fillWithRandomNumbers();
	b.fillWithRandomNumbers();

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	c = notVectorizedService.multiplyMatrices(a, b);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "It took (not_vec): " << time_span.count() << " seconds.";
	std::cout << std::endl;

	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	c = autoVectorizedService.multiplyMatrices(a, b);
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);
	std::cout << "It took (auto_vec): " << time_span2.count() << " seconds.";
	std::cout << std::endl;

	high_resolution_clock::time_point t5 = high_resolution_clock::now();
	d = sse.multiplyMatrices(a, b);
	high_resolution_clock::time_point t6 = high_resolution_clock::now();
	duration<double> time_span3 = duration_cast<duration<double>>(t6 - t5);
	std::cout << "It took (sse_vec): " << time_span3.count() << " seconds.";
	std::cout << std::endl;


	if (c->equals(d) == true) {
		std::cout << "equal";
	}
	else {
		std::cout << "not equal";
	}

	return 0;
}