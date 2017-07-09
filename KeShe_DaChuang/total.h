//
// Created by Famine on 2017/7/8.
//

#include "schedule.h"

#ifndef KESHE_DACHUANG_TOTAL_H
#define KESHE_DACHUANG_TOTAL_H

#endif //KESHE_DACHUANG_TOTAL_H

struct year {
    char nianfen[5];
    struct schedule *list[1000];
    int length;
    struct year *next;
    struct year *prior;
    int registeredProjectNum;
    int supportedProjectNum;
    int fund;
    float supportingRate;
    float passingRate;
    float excellentRate;
    float qualifiedRate;
    float unfinishedRate;
    int studentNum;

};

/*ͳ��ָ��ʱ�������ڸ������ȼƻ������걨����Ŀ�������֧�ֵ���Ŀ����
�ʽ� ֧���ʡ� ����ͨ���ʡ������ʡ��ϸ��ʡ�δ�����ʡ�����ѧ�������ȣ��Լ�
�ܵ��걨����Ŀ�������֧�ֵ���Ŀ����֧���ʡ�����ͨ���ʡ������ʡ��ϸ��ʡ�
δ�����ʵȡ� ��ָ��������걨�������֧�ֵ���Ŀ���� �ʽ������� ֧���ʡ�����
ͨ���ʵ�����û��ָ��ʱ������ʱΪ�м�¼���������������
ͳ��ָ��ʱ��������ָ��������ѧ���μӵ���Ŀ����Ŀ����������ͨ���ʡ���
�������ʡ�δ�����ʡ�֧��ģ����ѯ���ɰ�ѧ�š���������Ŀ����������ͨ���ʵ�
���� û��ָ��ʱ������ʱΪ�м�¼���������������

ͳ��ָ��ʱ����������ĳԺϵѧ���μӵ���Ŀ������ ����ͨ���ʡ����������ʡ�
δ�����ʵȡ�֧��ģ����ѯ���ɰ���Ŀ����������ͨ���ʡ����������ʡ�δ������
�Ӵ�С����û��ָ��ʱ������ʱΪ�м�¼���������������
ͳ��ָ��ʱ���ڵĸ�Ժϵ���봴�»�ı������������㹫ʽΪ��
������һ��ѧ��Ϊ��Ժϵ����Ŀ��/��Ŀ������
û��ָ��ʱ������ʱΪ�м�¼�����������Ŀ��������� ��������С�Ӵ�С
����*/

struct year *create();

void addData(struct year *, struct schedule *, char *, char *, char *);

void dataHandle(struct year *);