inherit ROOM;

void create()
{
        set("short", "�徻��");
        set("long", @LONG
������ȫ������֮ĩ��Ҳ��ΨһŮ�����ﲻ���ľ��ҡ���
���䴰��������������λʦ�ֵ����Ҵ���ͬ�������۵��ż�
���ۣ���������һ������ͷ��������ͷ�ɲ�������������˵ġ�
�ǵ������������ﲻ��Ϊͽʱ������һ������ͼ����������˼
��˵������̣��õ�Ϊ�����ﲻ������ʦ�����ͽ��������ͼ
�������Լ��ĵ����ϡ�
LONG);
        set("exits", ([
                "north" : __DIR__"nairongdian",
        ]));

        set("objects", ([
                CLASS_D("quanzhen") + "/sunbuer" : 1,
				//"/d/quanzhen/obj/bookshelf" : 1,
        ]));

        setup();
        replace_program(ROOM);
}