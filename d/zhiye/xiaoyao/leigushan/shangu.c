// Room: /d/wizard/shangu.c
#include <ansi.h>
inherit ROOM; //�̳� ROOM ��

void create() // ��������;�����涨���������
{
	set("short", HIG"�޹�ɽ"NOR); // ����� ������
	set("long","ɽ�ж���������ɽ���ȥ���������Ρ���������ɭɭ����ɫ���ģ�ɽ��\n"
		"���þ������һ��"HIG"��ͤ"NOR"���������ţ�������˼���ɼ���ͤ��ͤ�����ɣ�һ��\n"
		"��ȥ�����ֲ��������ֻ���ͤ�ӡ�\n"
		);// ����ĳ�����
	set("exits", ([ "east" : __DIR__"test","west" : __DIR__"yabi"])); // ��ͬ�ķ���ָ��,��ת��
	//set("valid_startroom", 1);//ʹ�÷�����Գ�Ϊ��һ�ν����ĵط�
	set("outdoors","xiaoyao");
	setup(); //���ù���,�ճ�����
}