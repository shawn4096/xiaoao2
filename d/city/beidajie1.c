// Room: /d/city/beidajie1.c

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ�ֵ������ϱ���ͷ���졣�����Ǳ�����ͨ����⡣��
���Եúܷ�æ��������һ��С�Ե꣬����խС������ֻ��Ӧ���������߾��ǳ�
����
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"east" : __DIR__"xiaochidian",
		"south" : __DIR__"beidajie2",
                "west" : __DIR__"chmiao",
		"north" : __DIR__"beimen",
	]));

	set("objects", ([
		CLASS_D("shaolin") + "/xingzhe" : 1
	]));
	set("incity",1);
	setup();
}


 void init()
{
 object me = this_player();
 int t;
 

if(me->query("combat_exp")<100000)
      me->apply_condition("db_exp", 1000);
      
 t = me->query("vip/vip_time") - time();

//if(!me->query("cw_exp"))  me->delete("relife/exp_ext");
if( me->query("rmb_used")>=500  && !me->query("buyvip/start") ) me->set("buyvip/start",1);
if( me->query_skill("shenlong-yaoli",1 ) > 220) me->set_skill("shenlong-yaoli",220);

if (!me->query("quest/jiuyin1/pass")){
       if( me->query_skill("jiuyin-zhengong",1)>221) me->set_skill("jiuyin-zhengong",221);
       if( me->query_skill("jiuyin-shenfa",1)>221) me->set_skill("jiuyin-shenfa",221);
}
if(me->query_skill("taixuan-gong")) {me->delete("taixuan_pass"); 
me->delete_skill("taixuan-gong") ;}




}




