//�ɹ����ָ��� by renlai

inherit FBROOM;

void create()
{
        set("short", "���湬-����");
        set("long", @LONG
��������������ǰ�ľ�ַ���������������˲�����֮ǰ
���޵ĵط��������ִ�ȫ��̺󣬴˵صĲ���ʵ��̫С���ͽ�
������Ǩ������ɽ�ϣ����˵����¸���Ϊ���湬���Լ���õ�
֮�⡣����ܾ�û���������ˣ������϶������˻ҳ���
LONG);
        set("outdoors", "����");
		set("backroom","/d/quanzhen/yuzhengong");
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
#include "fuben.h";
