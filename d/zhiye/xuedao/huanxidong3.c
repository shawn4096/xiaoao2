//huanxidong1.c

inherit ROOM;

void create()
{
        set("short", "�ϻ���");
        set("long", @LONG
����Ѫ�����ڵ��޻�ϲ��֮�أ����ڴ���һ���������֮����
��ʱ����Ů����ת�к͵����������˵İ���˻���������˲��ɵ�
Ѫ�����š�ǽ�ϻ����˺ܶั��Ů���ϵ�ͼ��(hua)��ÿһ�Ŷ���
�����룬˼����ǧ�����ߵ������ղ��ܡ�
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "east"   : __DIR__"huanxidong1",
			//"south"   : __DIR__"kengdao3",
        ]));
        set("item_desc", ([
            "hua"   : "���Թ�ӡ�ȵĹ�����Ů˫��֮����Ϊ�޻�ϲ��֮�˵�������\n",
        ]));
        set("objects",([
                __DIR__"obj/bed" : 1,
        ]));
        setup();
}
void init()
{

	add_action("do_canchan","canchan");
}
//������ϲ���չ�ǰ������Ѫս��Ȼ��չ�
int do_canchan(string arg)
{
	object me;
	me=this_player();


}