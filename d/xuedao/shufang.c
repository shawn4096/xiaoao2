// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
int do_fankan(string arg);
int do_search(string arg);

void create()
{
        set("short","���鶴");
        set("long",@LONG
Ѫ��������ս�����������������ָ��֣���ܺ�����Է��ؼ�
Ȼ��ȫ�������ڴˣ������е��Ӳ�����������(shujia)�ϰڷ�
��һ���ŵ������鼮����������������һ������Ĺ��񣬷���ׯ
�ϣ������°ڷ���һ�Ѷѵķ�Ҿ����ؼ������д󲿷־�Ϊ���ڵ�
��ϲ��(huanxi)����������
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
						   HIC"	Ѫ�����ķ���Ҫ(forcebook)��\n"+
						   HIR "	������������(bladebook),\n"+
						    HIY"	�����Ʒ���Ҫ(strikebook),\n"NOR,
		]));

        //	set("no_clean_up", 0);
        set("strikebook", 1);
		set("bladebook",1);
		set("huanxi",1);
		set("forcebook",1);

        setup();
        replace_program(ROOM);
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
	  
	  if (arg1=="huanxi" && this_object()->query("huanxi",1)<1)
		 return notify_fail("����ϡ��������úϻ������Ȿ���Ѿ����������ˣ���������\n");
	  if (arg1=="forcebook" && this_object()->query("forcebook",1)<1)
		 return notify_fail("����ϡ�Ѫ�����ķ���Ҫ���Ȿ���Ѿ����������ˣ���������\n");

	  if (arg1=="bladebook"&& this_object()->query("bladebook")<1)
		 return notify_fail("����ϡ������������š��Ȿ���Ѿ����������ˣ���������\n");
	  if (arg1=="strikebook"&& this_object()->query("strikebook")<1)
		 return notify_fail("����ϡ������Ʒ���Ҫ���Ȿ���Ѿ����������ˣ���������\n");

	   switch (arg1)
	   {
			  case "huanxi": 
				  ob=new("/d/xuedao/obj/huanxi_book1"); 
				  this_object()->add("huanxi",-1);
				 // ob->move(me);
				  break;             
			  case "strikebook": 
				  ob=new("/d/xuedao/obj/strike_book"); 
				  this_object()->add("strikebook",-1);
				 // ob->move(me);
				  break;   
			  case "bladebook": 
				  ob=new("/d/xuedao/obj/blade_rumen"); 
				  this_object()->add("bladebook",-1); 
				//  ob->move(me);
				  break;         
			  case "forcebook": 
				  ob=new("/d/xuedao/obj/xdj_book2"); 
				  this_object()->add("forcebook",-1); 
				//  ob->move(me);
				  break;   
			  default :
				  return notify_fail("û���Ȿ�顣\n");
		 }
	   if(present(ob, me) || present(ob, environment(me)))
		return notify_fail("�����ϻ�����Ѿ������������ˡ�\n");

    // ob->move(me);
	   if(ob) ob->move(me);
			message_vision("$N��������ó�һ��$n��\n",me, ob);  
       return 1; 

}