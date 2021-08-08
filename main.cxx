
#include <stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <random>
#include <ctime>
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

const int dim = 1;//ά��
const int p_num = 10;//��������
const int iters = 100;//��������
const int inf = 999999;//����ֵ
const double pi = 3.1415;
//�������ӵ�λ�ú��ٶȵķ�Χ
const double v_max = 4;
const double v_min = -2;
const double pos_max = 2;
const double pos_min = -1;
//����λ���������ٶ�����
vector<double> pos;
vector<double> spd;
//�������ӵ���ʷ����λ�ú�ȫ������λ��
vector<double> p_best;
double g_best;
//ʹ��eigen�ⶨ�庯��ֵ�����λ�þ���
Matrix<double, iters, p_num> f_test;
Matrix<double, iters, p_num> pos_mat;

//������Ӧ�Ⱥ���
double fun_test(double x)
{
    double res = x * x + 1;
    return res;
}

//��ʼ������Ⱥ��λ�ú��ٶ�
void init()
{
    //����������Ԫ�س�ʼ��Ϊ����ֵ
    f_test.fill(inf);
    pos_mat.fill(inf);
    //���ɷ�Χ�����
    static std::mt19937 rng;
    static std::uniform_real_distribution<double> distribution1(-1, 2);
    static std::uniform_real_distribution<double> distribution2(-2, 4);

    for (int i = 0; i < p_num; ++i)
    {
        pos.push_back(distribution1(rng));
        spd.push_back(distribution2(rng));
    }

    vector<double> vec;
    for (int i = 0; i < p_num; ++i)
    {
        auto temp = fun_test(pos[i]);//���㺯��ֵ
        //��ʼ������ֵ�����λ�þ���
        f_test(0, i) = temp;
        pos_mat(0, i) = pos[i];
        p_best.push_back(pos[i]);//��ʼ�����ӵ���ʷ����λ��
    }

    std::ptrdiff_t minRow, minCol;
    f_test.row(0).minCoeff(&minRow, &minCol);//���غ���ֵ�����һ���м�Сֵ��Ӧ��λ��
    g_best = pos_mat(minRow, minCol);//��ʼ��ȫ������λ��
}

void PSO()
{
    static std::mt19937 rng;
    static std::uniform_real_distribution<double> distribution(0, 1);
    for (int step = 1; step < iters; ++step)
    {
        for (int i = 0; i < p_num; ++i)
        {
        //�����ٶ�������λ������
            spd[i] = 0.5 * spd[i] + 2 * distribution(rng) * (p_best[i] - pos[i]) +
            2 * distribution(rng) * (g_best - pos[i]);
            pos[i] = pos[i] + spd[i];
            //���Խ����ȡ�߽�ֵ
            if (spd[i] < -2 || spd[i] > 4)
            spd[i] = 4;
            if (pos[i] < -1 || pos[i] > 2)
            pos[i] = -1;
            //����λ�þ���
            pos_mat(step, i) = pos[i];
        }
        //���º���ֵ����
        for (int i = 0; i < p_num; ++i)
        {
            auto temp = fun_test(pos[i]);
            f_test(step, i) = temp;
        }
        for (int i = 0; i < p_num; ++i)
        {
            MatrixXd temp_test;
            temp_test = f_test.col(i);//ȡ����ֵ�����ÿһ��
            std::ptrdiff_t minRow, minCol;
            temp_test.minCoeff(&minRow, &minCol);//��ȡÿһ�еļ�Сֵ��Ӧ��λ��
            p_best[i] = pos_mat(minRow, i);//��ȡÿһ�еļ�Сֵ����ÿ�����ӵ���ʷ����λ��
        }
        g_best = *min_element(p_best.begin(), p_best.end());//��ȡȫ������λ��
    }
    cout<< fun_test(g_best)<<endl;
}

int main()
{
    init();
    PSO();
    for (size_t i = 0; i < 5; i++)
    {
        sleep(1);
    }
    
    return 0;
}