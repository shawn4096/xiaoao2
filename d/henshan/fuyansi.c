#include <ansi.h>
inherit ROOM;

string look_duilian();

void create()
{
        set("short", "������");
        set("long", @LONG
������Ϊ�������滳�õĵ������������ڴ˺�������š�ɽ��
�����Ҷ���·�Ժ�����ǵ���д�գ�����������������ɲ  �����
�����ּ�������ɫ���š�ֻ��ɽ�ŵ�ǽ�����й�������(zi)�������
Զ���������ɱ硣�������ڵ�ʯ������һ����(lian)���ּ�Բ���ת��
��¶���档
LONG );
        set("exits", ([ 
                "southdown"  : __DIR__"shanlu9",
                "westup"     : __DIR__"sansheng",         
        ]));

        set("objects", ([
                __DIR__"npc/xiangke" : 2,
        ]));        

        set("item_desc", ([
            "zi":
HIW"\n
          �������з��  �������ߴ�����
          ʯ·���������  ɮ�����м�����
          ��յ��������  �����ɼ������
          �����Ϸ����ϴ�  ��̦��޺Զ���
\n\n"NOR,
            "lian" : (: look_duilian :),

        ]));

        //set("no_clean_up", 0);

   //     set("coor/x", -50);
//	set("coor/y", 20);
//	set("coor/z", 0);
	setup();
}


string look_duilian()
{
        return
        HIR "\n"
        "             ��������������            ��������������\n"
        "             ��������������            ��������������\n"
        "             ����      ����            ����      ����\n"
        "             ����" NOR + HIW "������" NOR + HIR "����            ����" NOR + HIW "  ��  " NOR + HIR "����\n"
        "             ������ �� ����            ����      ����\n"
        "             ����" NOR + HIW "  ��  " NOR + HIR "����            ����" NOR + HIW "  ��  " NOR + HIR "����\n"
        "             ����      ����            ����      ����\n"
        "             ����" NOR + HIW "  Ϊ  " NOR + HIR "����            ����" NOR + HIW "  Ϊ  " NOR + HIR "����\n"
        "             ����      ����            ����      ����\n"
        "             ����" NOR + HIW "  ��  " NOR + HIR "����            ����" NOR + HIW "  ��  " NOR + HIR "����\n"
        "             ����      ����            ����      ����\n"
        "             ����" NOR + HIW "  ɽ  " NOR + HIR "����            ����" NOR + HIW "  ��  " NOR + HIR "����\n"
        "             ����    ������            ����      ����\n"
        "             ����" NOR + HIW "  ��  " NOR + HIR "����            ����" NOR + HIW "  ��  " NOR + HIR "����\n"
        "             ����    ������            ����      ����\n"
        "             ����" NOR + HIW "  һ  " NOR + HIR "����            ����" NOR + HIW "  ��  " NOR + HIR "����\n"
        "             ����    ������            ����      ����\n"
        "             ����" NOR + HIW "  ��  " NOR + HIR "����            ����" NOR + HIW "  ��  " NOR + HIR "����\n"
        "             ����    ������            ����      ����\n"
        "             ����" NOR + HIW "  ɲ  " NOR + HIR "����            ����" NOR + HIW "  ��  " NOR + HIR "����\n"
        "             ����    ������            ����      ����\n"
        "             ��������������            ��������������\n"
        "             ��������������            ��������������\n\n" NOR;
}





