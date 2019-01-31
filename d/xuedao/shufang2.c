// shufang2.c
// sohu@xojh

#include <ansi.h>
inherit ROOM;
int do_fankan(string arg);
int do_search(string arg);

void create()
{
        set("short","���鶴����");
        set("long",@LONG
�˵���Ѫ���ż�Ϊ����֮��,û��������ɲ��ܵ�¥������ɱ����
����ǽ�����Ե�Ϊ�ʵ���˴�����ͼ�Σ�ͼ������С�ֽ���˵����������
�����ڴ˱չ������������á���Щ������Ѫ���Ų���֮�ء�
LONG );
        set("exits",([
                "south"   : __DIR__"lingwushi",
                //"southup" : __DIR__"nroad5",
        ]));
        set("objects",([				
				"/d/xuedao/npc/laoseng" : 1,
        ]));
		set("item_desc", ([
			"huanxi" : YEL"�����ϰڷ���һ���ŵĻ�ϲ�������ķ�̵伮,����ͨ��fankan���Ķ���\n"NOR,
			"shujia" : CYN"����Ϸ���һ�Ѷѵ������ؼ����󲿷�Ϊ�����ɵĵ��׺͹����书��\n"
						"����ͨ��search��Ѱ�Ҳ����ؼ��� \n"
					   HIM"	��ϲ�ھ�������(huanxi)��\n"+
						   HIR "	������������(basic),\n"+
						    HIY"	�����Ʒ���Ҫ(jingyao),\n"NOR,
		]));

        //	set("no_clean_up", 0);
        set("jingyao", 1);
		set("basic",1);
		set("huanxi",1);

        setup();
       // replace_program(ROOM);
}
void init()
{	
	add_action("do_search","search");
	add_action("do_fankan","fankan");

}

//���ŵĻ�ϲ������ 60
int do_fankan(string arg)
{
	object ob;
	mapping fam;
	object me=this_player();
	if (!arg||arg!="huanxi")
	{
		return notify_fail("��Ҫ����ʲô������\n");
	}

	if(me->query("potential", 1) < 1)
		return notify_fail("���Ǳ��û�ˣ������ټ�����ϰ��\n");
	if(!(fam = me->query("family")) || fam["family_name"] != "Ѫ����")
		return notify_fail("�㲻��Ѫ���ŵ��ӣ������������������Ļ�ϲ��Ҫ����\n");
	if(me->query("gender") == "����")
		return notify_fail("���޸����ԣ����������������������Ѫ���ž���������\n");
	if(me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ģ�\n");
	if(me->query("jing") < 25 )
		return notify_fail("��ľ���ܲ�, ����ȥ��Ϣһ��. \n");           
	if(me->query_skill("force", 1) < 20)
		return notify_fail("��Ļ����ڹ�̫��,����20�����޷���ϰ���߼����ڹ���\n");        
	//if(me->query_skill("xuedao-jing", 1) < 100)
		//return notify_fail("���Ѫ�����ڹ��ȼ�̫�ͣ��޷�����ϲ�伮�����֡�\n");
    if(me->query_skill("huanxi-chan", 1) > 60)
		return notify_fail("��Ļ�ϲ������һ�㣬���Գ���ѧϰ�߼���Ѫ���ž����������ˡ�\n");
	
	write(MAG"�㿪ʼ��ϰ�����ϵĻ�ϲ�����������������ĵá�\n"NOR);
	me->receive_damage("jing", 100 / (int)me->query("int"));
    me->improve_skill("huanxi-chan", me->query_int() + random(me->query_int() * 5 / 3));

	me->add("potential", -1);
	return 1;

}

int do_search(string arg)
{
	object ob;
	mapping fam;
	string arg1,arg2;
	object me=this_player();

	  if(!arg || sscanf(arg, "%s from %s", arg1, arg2)!=2)
		 return notify_fail("�����ʽ: search <�鱾����> from shujia��\n");
	  if (arg2!="shujia")
		 return notify_fail("�����ʽ: search <�鱾����> from shujia��\n");
	  if (query("huanxi")<1)
		 return notify_fail("������Ȿ���Ѿ����������ˣ���������\n");

	  if (query("basic")<1)
		 return notify_fail("������Ȿ���Ѿ����������ˣ���������\n");
	  if (query("jingyao")<1)
		 return notify_fail("������Ȿ���Ѿ����������ˣ���������\n");
	   switch (arg1)
	   {
			  case "huanxi": ob=new("/d/xuedao/obj/huanxi_book1"); add("huanxi",-1);break;             
			  case "jingyao": ob=new("/d/xueshan/obj/strike_book"); add("jingyao",-1);break;   
			  case "basic": ob=new("/d/xueshan/obj/bladebasic_book"); add("basic",-1); break;         
			  default :
					 return notify_fail("û���Ȿ�顣\n");
		 }
	 if(present(ob, me) || present(ob, environment(this_object())))
		return notify_fail("�����ϻ�����Ѿ������������ˡ�\n");
     if(ob) ob->move(me);
       message_vision("$N��������ó�һ��$n��\n",me, ob);  
       return 1; 

}