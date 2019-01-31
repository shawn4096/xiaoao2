// huacong.c
// By River@SJ 98/08/29

#include <ansi.h>
inherit ROOM;

void delete_hexiu(object me, object arg);

void create()
{
	set("short",HIR"�컨��"NOR);
	set("long", @LONG
��Ժ컨�ſ����������ɣ����ܲ�㣬�����˱ǣ�������������һ������
�磬�����֦��ɷ�Ǻÿ������������񴹸ǣ�������Ȼ��ɵ�һ���������ݡ�
���ܶ���һƬ���ģ�ֻ��Ȫ����������˼���ȷ�Ǹ��Ϻõ��������ڡ�
LONG        );

	set("exits", ([
		"west" : __DIR__"guolin4",
		"south" : __DIR__"guolin5",
	]));

	set("outdoors","��Ĺ");

	set("no_fight", 1);
	setup();
}

void init()
{
	object me=this_player();

	add_action("do_hexiu", "hexiu");
	add_action("do_quit", "quit");
	if (me->query_temp("ynxj/hexiusun"))
	{
		if (!present("sun popo",environment(me)))
		{
			new("kungfu/class/gumu/sun")->move(environment(me));
		}
	}
}

int do_hexiu(string arg)
{
	object me = this_player();
	object ob, *inv;
	mapping fam;
	int ynlvl,i;

	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");
	
	if(!arg)
		return notify_fail("��Ҫ��˭�����ڹ���\n");

	if (!(fam = me->query("family")) || fam["family_name"] != "��Ĺ��")
		return notify_fail("�㲻�ǹ�Ĺ�ɴ��ˣ���ô������Ĺ���ڹ���\n");

	if (me->query("gender") == "����")
		return notify_fail("���޸����ԣ������������������������Ů�ľ��񹦡�\n");
    
	if (!(ob = present(arg, this_object())))
		return notify_fail("�������ڲ������\n");

	if ( me == ob)
		return notify_fail("������˫�ֻ�����\n");

	if (!living(ob))
		return notify_fail("������Ȱ�" + ob->name() + "Ū�ѡ�\n");
	

	if( me->query_temp("weapon"))
		return notify_fail("������������������ô˫����ԣ�������Ů�ľ���\n");

	ynlvl = me->query_skill("yunu-xinjing",1);

	if ( me->query("potential") < 1 )
		return notify_fail("���Ǳ�����Ĺ��ˣ���ʱ�޷����ޡ�\n");

	if( userp(ob) && ob->query("potential") < 1)
		return notify_fail( ob->name()+"��Ǳ�����Ĺ��ˣ���ʱ�޷����ޡ�\n");

	//if ( ob->query_skill("yunu-xinjing", 1) < (ynlvl - 100))
		//return notify_fail(ob->name() +"�����������̫Զ���޷�����������\n");

	if (me->query("jing") < 30 || me->query("qi") < 30)
		return notify_fail("��̫���ˣ���������Ϣһ����ɣ�\n");

	if (ob->query("jing") < 30 || ob->query("qi") < 30)
		return notify_fail(ob->name()+"̫���ˣ���������Ϣһ����ɣ�\n");
	//�������ź���
	if (me->query_temp("ynxj/hexiusun"))
	{
		call_out("hexiu_sun",1,me,ob);
		return 1;
	}
	if (!userp(ob))
		return notify_fail("��ֻ������Һ���������\n");
	if (me->query_temp("gumu_hexiu")
	 && me->query_temp("gumu_hexiu")!= ob->query("id"))
		return notify_fail("����������˺����أ�\n");

	inv= all_inventory(me);
	i = sizeof(inv);
	while (i--)
	if( inv[i]->query("equipped") && (! inv[i]->query_autoload() && inv[i]->query("id") != "lingpai"))
		return notify_fail("����㲻��ȥ�����������������п��ܻ��߻���ħ��\n"); 

	me->set_temp("gumu_hexiu", ob->query("id"));
	ob->set_temp("gumu_hexiu", me->query("id"));
	tell_object(ob,"�컨���У�"+me->name()+"����������ǰ�������������Ů�ľ���\n");
	tell_object(me,"�컨���У��������"+ob->name()+"��ǰ�������������Ů�ľ���\n");

	if ( ob->query_temp("gumu_hexiu") 
	 && ob->query_temp("gumu_hexiu") != me->query("id"))
		return notify_fail(ob->name()+"û��Ҫ���������������˼��\n");

	if (!ob->query_temp("gumu_hexiu")) return 1;
	message_vision(HIW"\n$N���͸�����ԣ���$n������֣����˸�������һ�ߣ��⿪��������ϰ������\n"NOR,me, ob);
	me->start_busy(15);
	ob->start_busy(15);
	call_out("delete_hexiu", 2+random(3), me, ob);
	return 1;
}

void delete_hexiu(object me, object ob)
{
	if ( !me || !ob) return;

	me->receive_damage("jing", 20+random(10),"�߻���ħ��");
	me->receive_damage("qi",  20+random(5),"�߻���ħ��");
	me->add("potential", -1);
	if ( me->query_skill("yunu-xinjing", 1) < 220 )
		me->improve_skill("yunu-xinjing", me->query_int()*2);
	
//	if (!me->query_temp("ynxj/hexiusun"))
	 //  me->add("combat_exp",1000+random(500));
	me->start_busy(1);
	me->delete_temp("gumu_hexiu");

	ob->receive_damage("jing", 20+random(10),"�߻���ħ��");
	ob->receive_damage("qi",  20+random(5),"�߻���ħ��");
	ob->add("potential", -1);
	//if ( ob->query_skill("yunu-xinjing", 1) < 130 )
    //ob->improve_skill("yunu-xinjing", ob->query_int()*( 8 + random(20))); 
	//if (!me->query_temp("ynxj/hexiusun"))
		//ob->add("combat_exp",1000+random(500));
	ob->start_busy(1);
	ob->delete_temp("gumu_hexiu");
	if (me->query("quest/gumu/ynxj/pass"))
	{
		message_vision(HIR"���Ѿ���������Ů�ľ���һ�ΰ��أ����޶�����˵�Ѿ�û��ʲô���塣\n"NOR,me);
		return;
	}
	if (time()-me->query("quest/gumu/ynxj/time")>86400) 
	{
		//һ��֮�ڲ��л���
		//write("eeeee");
		message_vision(HIY"$N��$n˫����֣�������ӿ�������ڹ������������ĵã���ǰ��Ȼ����һƬ��Ȼ���ʵĸо���\n"NOR,me,ob);
      
		remove_call_out("lingwu_ynxj");
		call_out("lingwu_ynxj",1,me,ob);
	}
	
	message_vision(HIR"\n���ú�$N��$n�ܵ���Ӧ����ʱ�˹�Ϊ����ȫ���������ڣ��ջ��ķᡣ\n\n"NOR,me,ob);
	if (userp(ob)) message_vision(HIC"\n$N��$n�о��Լ����һ���ľ���ֵ������\n"NOR,me,ob);
	me->delete_temp("ynxj/hexiusun");
	return;
}

int do_quit()
{
	write("���ﲻ׼�˳���\n");
	return 1;
}

int valid_leave(object me, string dir)
{
	me->delete_temp("gumu_hexiu");
	return ::valid_leave(me, dir);
}

int hexiu_sun(object me,object ob)
{
	object sun;	
	object *inv;
	int ynlvl,i;
	/*if (!objectp(sun=present("sun popo",find_object("d/gumu/rukou.c"))))
		if (!present("sun popo",environment(me)))
		{
			sun=new("kungfu/class/gumu/sun");
			sun->move(environment(me));
		}*/
	
	message_vision(HIY"\n$N���ҿ��˿����˴����ˣ����Ǻ�������������~~~~~����������\n"NOR,me);
	message_vision(HIC"\n\n�������੹�Цһ������СѾͷ���������ˣ�\n"NOR,me);	
	

	if( me->query_temp("weapon"))
		return notify_fail("������������������ô˫����ԣ�������Ů�ľ���\n");
	ynlvl = me->query_skill("yunu-xinjing",1);

	if ( me->query("potential") < 1 )
		return notify_fail("���Ǳ�����Ĺ��ˣ���ʱ�޷����ޡ�\n");

	//if( ob->query("potential") < 1)
		//return notify_fail( ob->name()+"��Ǳ�����Ĺ��ˣ���ʱ�޷����ޡ�\n");

//	if ( ob->query_skill("yunu-xinjing", 1) < (ynlvl - 100))
//		return notify_fail(ob->name() +"�����������̫Զ���޷�����������\n");

	if (me->query("jing") < 30 || me->query("qi") < 30)
		return notify_fail("��̫���ˣ���������Ϣһ����ɣ�\n");

	//if (ob->query("jing") < 30 || ob->query("qi") < 30)
	//	return notify_fail(ob->name()+"̫���ˣ���������Ϣһ����ɣ�\n");
	if (me->query_temp("gumu_hexiu")
	 && me->query_temp("gumu_hexiu")!= ob->query("id"))
		return notify_fail("����������˺����أ�\n");

	inv= all_inventory(me);
	i = sizeof(inv);
	//while (i--)
	//if( inv[i]->query("equipped") && (! inv[i]->query_autoload() && inv[i]->query("id") != "lingpai"))
		//return notify_fail("����㲻��ȥ�����������������п��ܻ��߻���ħ��\n"); 
	
	
	me->set_temp("gumu_hexiu", ob->query("id"));
	ob->set_temp("gumu_hexiu",me->query("id"));
	tell_object(ob,"�컨���У�"+me->query("name")+"����������ǰ�������������Ů�ľ���\n");
	tell_object(me,"�컨���У��������"+ob->query("name")+"��ǰ�������������Ů�ľ���\n");

	if ( ob->query_temp("gumu_hexiu") 
	 && ob->query_temp("gumu_hexiu") != me->query("id"))
		return notify_fail(ob->name()+"û��Ҫ���������������˼��\n");

	if (!ob->query_temp("gumu_hexiu")) return 1;
	message_vision(HIW"\n$N���͸�����ԣ���$n������֣����˸�������һ�ߣ��⿪��������ϰ������\n"NOR,me, ob);
	me->start_busy(10);
	ob->start_busy(10);
	call_out("delete_hexiu", 2+random(3), me, ob);
	return 1;

}

//huacong ����

int lingwu_ynxj(object me,object ob)
{
	int i,j;
	object sun;
	if (me->query("quest/gumu/ynxj/pass"))
	{
		return notify_fail("���Ѿ��⿪�����⣬��Ϲ����ʲô��");
	}
	message_vision(HIM"��Ժ컨�ſ����������ɣ����ܲ�㣬�����˱�,��ҹ֮�У��������Ũ����$N��$n�������Ը����ù���\n"HIY"$N��$nȫ���������ڣ����ǻ���һ޹�����Ƿҷ������\n"NOR,me,ob);
	
	if(me->query_temp("canwu_hexiu")<(10+random(5)))
    { 
	  me->add_temp("canwu_hexiu",1);
      if(random(2)) tell_object(me,HIG"\n����Ů�ľ������й��ǡ���������˫��Ϊ�����ˡ����������ǡ����ˡ�������ʱ������ֹ��\n"NOR);
             else tell_object(me,HIY"\n�Է����ġ�������ȴ��һ���ǳɣ���;����΢�жٴ졣ͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  //remove_call_out("lingwu_ynxj");
	  call_out("lingwu_ynxj",3+random(3), me,ob);
	  return 1;
	}
   else
   {  
	  me->delete_temp("canwu_hexiu");
      if (userp(ob)) j=15;
      else j=20;

	  
      if(me->query("m-card-vip")) j =  j-1;
      if(me->query("y-card-vip")) j =  j-3;
      if(me->query("buyvip"))     j =  j-5;
	  if (me->query("gender")=="Ů��")
	     j=j-1;
	 
	  i= random(j);

     if(i<3
		 && random(me->query_int())>40
		 && random(me->query("kar"))>20)
	 {
		tell_object(me,HIM"\n�㰴�չ�Ĺ����Ů�ľ���Ҫ��ָ�㣬����������֮���������˽⣬��Ů�ľ��İ����ƺ���Щ����Ӧ�֡�\n"NOR);
        tell_object(me, HIG"ͻȻ�䣬��ֻ������Ϣ���ԡ�β��Ѩ������������ᡢ���ء����š�����\n"+
"��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������\n"+
"��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
		tell_object(me,HIY"\n������ǧ����࣬���ڵó���Ը������Ů�ľ�����С�ɡ�\n"NOR);
       	
		me->improve_skill("yunu-xinjing", 15+random(10));
		
		me->set("quest/gumu/ynxj/pass",1);
		me->set("quest/gumu/ynxj/time",time());
		me->start_busy(1);

		log_file("quest/ynxjronghe", sprintf("%8s(%8s) ʧ��%d�κ�������Ů�ľ����ںϾ�����һ�Ρ�iȡֵ��%d|���飺%d��\n", me->query("name"),me->query("id"), me->query("quest/gumu/ynxj/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gumu/ynxj/fail",1);
		
		tell_object(me,HBYEL+HIW"\n��ͶԷ���������Ů�ľ��ںϵİ��أ�ʼ��ȫȻ����Ҫ�졣\n\n"NOR);
		tell_object(me,HIG"\n������Ů�ľ���һ��ʧ�ܡ��ٽ�������\n\n"NOR);
		me->start_busy(1);
		me->add("quest/gumu/ynxj/fail",1);
		me->set("quest/gumu/ynxj/time",time());
//		write("222");

		if (objectp(sun=present("sun popo",environment(me))))
			destruct(sun);	
		log_file("quest/ynxjronghe", sprintf("%8s(%8s) ��Ů�ľ���һ�ν���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->query("name"),me->query("id"),me->query("quest/gumu/ynxj/fail"),i,me->query("combat_exp")) );
	  }
	return 1; 
  }

}
