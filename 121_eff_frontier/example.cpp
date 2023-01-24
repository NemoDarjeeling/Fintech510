#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>

using namespace Eigen;
using namespace std;


void readAsset(vector<vector<string> >& temp, string path) {
	ifstream inFile(path);
	if (!inFile) {
		cerr << "No such file!" << endl;
		exit(1);
	}
	string lineStr;
	while (getline(inFile, lineStr)) {
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		while (getline(ss, str, ',')) {
			if (str == "") {
				cerr << "asset error" << endl;
				exit(1);
			}
			lineArray.push_back(str);
		}
		temp.push_back(lineArray);
	}
}

void getAvgRORAndStandardDev(vector<vector<string> >temp, vector<double>& a, vector<double>& b) {
	int len = temp.size();
	for (int i = 0; i < len; ++i) {
		a.push_back(stod(temp[i][1]));
		b.push_back(stod(temp[i][2]));
	}
}

vector<vector<double> > getCorr(string path) {
	vector<vector<double> >c;
	ifstream inFile(path);
	if (!inFile) {
		cerr << "No such file!" << endl;
		exit(1);
	}
	string lineStr;
	while (getline(inFile, lineStr)) {
		stringstream ss(lineStr);
		string str;
		vector<double> lineArray;
		while (getline(ss, str, ',')) {
			if (str == "") {
				cerr << "corr error" << endl;
				exit(1);
			}
			lineArray.push_back(stod(str));
		}
		c.push_back(lineArray);
	}
	return c;
}

vector<vector<double> > getCov(vector<double>b,vector<vector<double> >c) {
	vector<vector<double> >ans;
	int len = c.size();
	ans.resize(len);
	for (int i = 0; i < len; ++i) {
		int t_len = c[i].size();
		ans[i].resize(t_len);
		for (int j = 0; j < t_len; ++j) {
			if (i == j) {
				ans[i][j] = b[j] * b[j];
			}
			else {
				ans[i][j] =c[i][j] * b[i] * b[j];
			}
		}
	}
	return ans;
}

vector<vector<double> > LeftMartix(vector<double>a, vector<vector<double> >c) {
	vector<vector<double> >e;
	int aLen = a.size(), cRow = c.size(), cCol = c[0].size();
	e.resize(cRow + 2);
	for (int i = 0; i < cRow + 2; ++i) {
		e[i].resize(cCol + 2);
	}

	for (int i = 0; i < cRow; ++i) {
		for (int j = 0; j < cCol; ++j) {
			e[i][j] = c[i][j];
		}
	}

	for (int i = 0; i < aLen; ++i) {
		e[i][aLen] = 1;
		e[i][aLen + 1] = a[i];

		e[aLen][i] = 1;
		e[aLen + 1][i] = a[i];
	}

	for (int i = cRow; i < cRow + 2; ++i) {
		for (int j = cCol; j < cCol + 2; ++j) {
			e[i][j] = 0;
		}
	}
	return e;
}


MatrixXd RightMartix(double Rp, int n) {
	MatrixXd f(n + 2, 1);
	for (int i = 0; i < n; ++i) {
		f(i, 0) = 0;
	}
	f(n, 0) = 1;
	f(n + 1, 0) = Rp;
	return f;
}

vector<vector<double> > newLeftMartix(vector<vector<double> >e, MatrixXd ans) {
	vector<vector<double> >g = e;
	int row = ans.rows() - 2;
	for (int i = 0; i < row; ++i) {
		if (ans(i, 0) < 0.0) {
			int index = i;
			vector<vector<double> >temp = g;
			g.resize(temp.size() + 1);
			int rowNum = temp.size(), colNum = temp[0].size(), len = g.size();
			for (int j = 0; j < len; ++j) {
				g[j].resize(colNum + 1);
			}
			for (int j = 0; j < rowNum; ++j) {
				for (int k = 0; k < colNum; ++k) {
					g[j][k] = temp[j][k];
				}
			}
			int t_len = g[0].size();
			for (int j = 0; j < len; ++j) {
				g[j][t_len - 1] = 0;
			}
			for (int j = 0; j < t_len; ++j) {
				g[len - 1][j] = 0;
			}
			g[index][t_len - 1] = 1;
			g[len - 1][index] = 1;
		}
	}
	return g;
}


MatrixXd newRightMartix(MatrixXd ans) {
	int flag = 0, row = ans.rows();
	for (int i = 0; i < row - 2; ++i) {
		if (ans(i, 0) < 0.0) {
			++flag;
		}
	}
	MatrixXd h(row + flag, 1);
	for (int i = 0; i < row; ++i) {
		h(i, 0) = ans(i, 0);
	}
	for (int i = row; i < row + flag; ++i) {
		h(i, 0) = 0;
	}
	return h;
}

MatrixXd vectorToMatrix(vector<vector<double> >t) {
	MatrixXd matrix(t.size(), t[0].size());
	int row = t.size();
	for (int i = 0; i < row; ++i) {
		int col = t[0].size();
		for (int j = 0; j < col; ++j) {
			matrix(i, j) = t[i][j];
		}
	}
	return matrix;
}


int main(int argc, char** argv) {
	bool rFlag = false;
	if (argc != 3 && argc != 4) {
		cerr << "arguments error" << endl;
		exit(1);
	}
	if (argc == 4) {
		if (argv[1] == "-r") {
			rFlag = true;
		}
		else {
			cerr << "error" << endl;
			exit(1);
		}
	}
	vector<vector<string> >temp;
	vector<double>avgROR, StandardDev;
	vector<vector<double> >cov, e, corr;
	readAsset(temp, "C:\\Users\\fishcy\\Desktop\\universe.csv");
	//readAsset(temp, argv[1]);
	getAvgRORAndStandardDev(temp, avgROR, StandardDev);
	corr = getCorr("C:\\Users\\fishcy\\Desktop\\correlation.csv");
	cov = getCov(StandardDev,corr);
	//corr = getCorr(argv[2]);
	//cov = getCov(StandardDev,corr);
	e = LeftMartix(avgROR, cov);
	MatrixXd left = vectorToMatrix(e);
	
    cout << "ROR,volatility" << endl;
	for (double k = 0.01; k < 0.27; k += 0.01) {
		MatrixXd right = RightMartix(k, avgROR.size());
		cout << fixed << setprecision(1) << k * 100.0 << "%,";
		MatrixXd x = left.fullPivLu().solve(right);
		cout << x << endl;
		if (!rFlag) {
			MatrixXd newleft = vectorToMatrix(newLeftMartix(e, x));
			right = newRightMartix(x);
			x = newleft.fullPivLu().solve(right);
			int row = cov.size();
			double ans = 0;
			for (int i = 0; i < row; ++i) {
				int col = cov[i].size();
				for (int j = 0; j < col; ++j) {
					ans += x(i, 0) * x(j, 0) * StandardDev[i] * StandardDev[j] * corr[i][j];
				}
			}
			cout << fixed << setprecision(2) << sqrt(ans) * 100.0 << "%" << endl;
		}
		else {
			int row = cov.size();
			double ans = 0;
			for (int i = 0; i < row; ++i) {
				int col = cov[i].size();
				for (int j = 0; j < col; ++j) {
					ans += x(i, 0) * x(j, 0) * StandardDev[i] * StandardDev[j] * corr[i][j];
				}
			}
			cout << fixed << setprecision(2) << sqrt(ans) * 100.0 << "%" << endl;
		}
	}
}
