// lgxys.c
// ½������ҩ��

inherit ROOM;
void create()
{
	set("short","��ҩ��");
	set("long",@long
����������������ҩ�ң������л���½��������һ���ţ����ŵ���Ũ
�Ĳ�ҩζ�����ϰڷ���һ���޴����ҩ¯���в��ٵ����ڴ�æµ����Щҩʦ
���ڵ��ϰ�æ�ּ�ҩ�ݡ�
long);
	set("exits",([
	    "east" : __DIR__"lgxroom",
	]));
	set("objects",([
		__DIR__"npc/obj/yaolu" : 1,
		__DIR__"npc/yunsumei" : 1,
	]));
	//set("yaozhong",15);
     setup();
}
