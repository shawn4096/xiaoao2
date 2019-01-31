// zhushao
// 98.8.5  by emnil
// 10/6/2001 by augx@sj

#include <ansi.h>
inherit ITEM;
int she_come(object me,object ob);

void create()
{
	set_name(HIB"�����"NOR, ({ "cuizhu di","di","zhudi" }) );
	set("long",HIY"����һֻ�����ߵ����Բ��Ĵ������̵ĵ��ӣ��˵�����Ҫ��ѱ��ʹ�á�\n"
		"����ͨ������ָ�����ﵽѵ���ߵ�Ŀ�ģ�\n"NOR
		HIG"zhaoshe  ����ָ������һ���ط������߹���ָ���ָ����ʱ�޶������ߵ�����\n"
		"��ָ����������ߵķ����ڣ�����Զ������ʱ��ϳ���\n"NOR
		HIC"qushe   : (qushe xx)ѵ������ʹ�ߵĶ���(���ڷ����� qushe east ,�������ҷ�����)��\n"NOR
		HIR"anfu :��anfu xx�����ڴ��ڱ���͹�������ߵİ�������,����ָ�����\n"NOR
		HIG"fangshe  ��(fangshe xx)���߷��ߡ�\n"NOR
		HIM"��Ҫע����ǣ�ѵ��ʧ�ܻᵼ���߶���Ĺ���,�ʵ�������ҩ���ۻ��Ǻ���Ҫ�ģ�\n"NOR);
	set("unit", "ֻ");
	set("weight", 50);
	set("no_sell",1);
	set("no_get",1);
	set("no_steal",1);
	set("no_drop",1);
	//set("no_give",1);
	set("value", 1);
} 

void init()
{
	add_action("do_anfu","anfu");
	add_action("do_zhaoshe","zhaoshe");
	add_action("do_fangshe","fangshe");
	
	//add_action("do_nashe","nashe");
	//add_action("do_chushe","chushe");
	add_action("do_xunshe","qushe");
	//add_action("do_huti","huti");
	//add_action("do_gongji","gongji");
}
//����

int do_zhaoshe(string arg)
{ 
	object me,ob,room;
	
	
	me = this_player();
	room=environment(me);
	if (!me->query_temp("sld/qushe/start"))
		return notify_fail("���ó���Ѵ������������������ҵ��٣�\n");
	
	if( me->query_temp("sld/qushe/zhaoshe") )
		return notify_fail("���Ѿ��ҵ������Ŀ�����أ�\n");
	
	if( (int)me->query_temp("sld/qushe/qushe") )
		return notify_fail("������ѵ����...��\n");
	
	if(!environment(me)->query("canfindsnake"))
		return notify_fail("���������Ҳ����ߡ�\n");
	
	if((int)me->query("jingli")<200)
		return notify_fail("��ľ�������200��\n");
	if((int)me->query_skill("shenlong-yaoli",1) < 100) 
		return notify_fail("�������ҩ����Ϊ����100�����������ߡ�\n");
	if((int)me->query_skill("dulong-dafa",1) < 100) 
		return notify_fail("��Ķ�������Ϊ����������ѱ�ߡ�\n");
	if((int)me->query_skill("poison",1) < 100) 
		return notify_fail("��Ķ�����Ϊ����������ѱ�ߡ�\n");
	if (me->is_busy()||me->is_fighting())
		return notify_fail("������æµ����΢��Ϣ���ٴ���\n");
	if (room->query("outdoors")!="������")
	{
		return notify_fail("ֻ�������������ʢ�����ߣ�\n");
	}
	if (me->is_busy()||me->is_fighting())
		return notify_fail("������æµ�У��޷�Ѱ���ߡ�\n");
	
	message_vision(HIG"$N�ó���ѣ����ĵĴ���������������Щ�̶���ʹ�˲��Ծ��ľ�����Щ���з��}�ĸо���\n"NOR,me);

	if (random(me->query("kar"))>10)
	{
			message_vision(HIY"\n\n������ģ��������ߺ�Ȼ���ף������������������ӿ����\n"NOR,me);
			if (!objectp(ob=find_object(me->query("id")+"'s xunshe")))
			
			ob=new("/d/sld/npc/obj/snake");
			me->set_temp("sld/qushe/zhaoshe",1);
			call_out("she_come",6+random(4),me,ob);

	}
	else message_vision(YEL"�ƺ�Զ������һ��ɳɳ������.......�ƺ�����...�����˰���ȴ��û���˴�.....��\n"NOR,me);

	
	me->receive_damage("jingli",100+random(100));
	me->add_busy(5+random(2));
	
	return 1;	

}

int she_come(object me,object ob)
{
	int lvl,exp;
	
	if (!objectp(ob)) return notify_fail("��û���ҵ��ߡ�\n");
	
	ob->set("owner",me->query("id"));
	
	ob->set_name(me->query("name")+HIG"��ѵ��"NOR, ({ me->query("id")+"'s xunshe","xunshe","she" }) );
	
	message_vision(HIG"\n$n"HIG"����������������ͷ��������о��Χ��$N�ĸ�ǰ����֮������������һ��������\n"NOR,me,ob);

	exp = me->query("combat_exp"); 
	if( exp < 100000) exp = 100000;
	
	ob->set("combat_exp",exp);
	ob->set("long",ob->query("long")+HIC"�������"+me->query("name")+HIC"��ѵ���ĳ����ߣ�\n"NOR);
	ob->set("max_qi",me->query("max_qi"));
	ob->set("eff_qi",me->query("max_qi"));
	ob->set("qi",me->query("max_qi"));  
	ob->set("max_jing",me->query("max_jing"));
	ob->set("eff_jing",me->query("max_jing"));
	ob->set("jing",me->query("max_jing")); 
	
	ob->set("max_neili",me->query("max_neili"));
	ob->set("neili",me->query("max_neili"));
	ob->set("eff_jingli",me->query("eff_jingli"));
	ob->set("jingli",me->query("eff_jingli"));
	lvl = me->query("max_pot") - 100;
	ob->set_skill("force",lvl);
	ob->set_skill("dodge",lvl);
	ob->set_skill("parry",lvl);
	ob->set_skill("poison",lvl);
	ob->set_temp("apply/attack",lvl);
	ob->set_temp("apply/dodge",lvl);
	ob->set_temp("apply/parry",lvl);
	ob->set_temp("apply/force",lvl);
	ob->set_temp("apply/defense", lvl);
	ob->set_temp("apply/damage",(lvl/10)>20?(lvl/10):20);
	ob->set_temp("apply/armor", (lvl/3)>50?(lvl/3):50);
	//ob->set_temp();
	ob->move(environment(me));
	me->set_temp("sld/qushe/zhaoshe",1);
	this_object()->set_temp("sld/qushe/zhaoshe",1);
	return 1;

}
//�������ƶ�Ŀ��
int do_xunshe(string arg)  
{
	object me,ob,room;
	
	string dir,exit;
	int ap,dp,i,j;
	me = this_player();
	room=environment(me);
	//exit=room->query("exits");
	
	if( !me->query_temp("sld/qushe/zhaoshe") )
		return notify_fail("��û���ҵ��ߡ�\n");
 	if( !objectp(ob=present(me->query("id")+"'s xunshe",environment(me))) )
		return notify_fail("��û����Ҫ�ҵ��ߡ�\n");
	//ob����Ŀ����
	
	if (ob->query("owner")!=me->query("id"))
		return notify_fail("�ǲ������ߣ���ʹ���ˡ�\n");
	
	ap=me->query_skill("qusheshu",1)*me->query_int()+me->query("combat_exp");
	dp=ob->query("combat_exp");
	
	if (me->is_busy()||me->is_fighting())
		return notify_fail("������æµ�У��޷��������ߡ�\n");

	switch(arg) {
		case "e":	dir="east"; break;
		case "w":	dir="west"; break;
		case "n":	dir="north"; break;
		case "s":	dir="south"; break;
		case "ne":	dir="northeast"; break;
		case "nw":	dir="northwest"; break;
		case "se":	dir="southeast"; break;
		case "sw":	dir="southwest"; break;
		case "u":	dir="up"; break;
		case "d":	dir="down"; break;
		case "nu":	dir="northup"; break;
		case "eu":	dir="eastup"; break;
		case "su":	dir="southup"; break;
		case "wu":	dir="westup"; break;
		case "nd":	dir="northdown"; break;
		case "ed":	dir="eastdown"; break;
		case "sd":	dir="southdown"; break;
		case "wd":	dir="westdown"; break;
		case "out": dir="out"; break;
		//case "l":	dir="look"; break;
		default:	dir=arg; break;
	}
	if (!arg||!dir)
		return notify_fail("��Ҫָ������δ�ȥ����\n");
	
	exit=room->query("exits/"+dir);
	
	if (!exit) {
		return notify_fail("�������û�г�·��\n");		
	}
	
	message_vision(HIB"$Nƽ�ľ������������ѣ�������ת�������ͼ��ʹ$n��"HIY+dir+HIB"�ķ����ȥ!\n"NOR,me,ob);
	
	if (random(ap)>dp/3)
	{
		me->set_temp("sld/qushe/qushe",1);
		me->start_busy(1);
		call_out("she_move",1+random(2),me,ob,dir);
	}else
	{
		message_vision(HIR"$n��������ʹ���ã��·����ǲ��ͣ����Դ󷢣�תͷһ��ҧ��$N��\n"NOR,me,ob);
		ob->kill_ob(me);
		
	}
	//��������
	if (objectp(ob)&&ob->query_temp("qushe/ok"))
	{
		tell_object(me,HIY"����$n�������ƺ���Щ���ˣ�������˳������������֮�У�\n"NOR,me,ob);
		ob->move(me);
	}
	return 1;  
}
//���ƶ�ָ��
int she_move(object me,object ob,string arg)
{

	if (!me||!ob) return 0;
	
	message_vision(HIM"$n��������$N��ָ�ӣ��ƺ�������$N��������˼����$Nָ�ӵ�"HIY+arg+HIB"�����ȥ!\n"NOR,me,ob);
	me->add_temp("sld/qushe/times",1);
	
	me->improve_skill("qusheshu",me->query_int());
	ob->do_command(arg);
	return 1;
}
//������ŭ����
int do_anfu(string arg)
{
	object me,ob;
	me=this_player();
	
	if (!arg) return notify_fail("��Ҫ����ɶ��");
	
	//if (objectp(ob=present(arg,environment(me))))
	ob=present(arg,environment(me));
	if (!ob) return notify_fail("��Ҫ���Ѱ���˭��\n");
	
	if (ob->query("id")!=me->query("id")+"'s xunshe")
	{
		return notify_fail("��ֻ�ܰ����Լ���ѵ�ߣ�\n");
	}
	if (!ob->is_fighting())
	{
		return notify_fail("���ѵ���Ѿ�����˳�ˣ�\n");
	}
	if (!random(10)) 
	{
		message_vision(HIW"$N����������һ���������ɣ�$n"HIW"�����ƺ���Ȼ���겻�ѣ�\n"NOR,me,ob);
		
	}else {
		message_vision(HIW"$N����������һ���������ɣ�$n"HIW"���˺��ƺ���Щ����������\n"NOR,me,ob);
		ob->remove_all_killer();
		me->improve_skill("qusheshu",me->query_int());
	}
	me->add_busy(1);
	return 1;
}

//����
int do_fangshe(string arg)      
{
	object me,ob;
//	object * all;
	me = this_player();

	if (!arg) return notify_fail("��Ҫ����ʲô���");
	
	//if (objectp(ob=present(arg,environment(me))))
	ob=present(arg,me);
	
	if (!ob) return notify_fail("��ĳ��ﲻ�������ϣ�\n");
	
	if (ob->query("owner")!=me->query("id"))
		return notify_fail("���Ҷ���û���ܹ���ѱ�����߲����ҷš�\n");
	
	if( !me->query_temp("sld/qushe/zhaoshe")
		|| !me->query_temp("sld/qushe/qushe") )
		return notify_fail("��û�����߳ɹ����Ҳ������ʵ��߷�����\n");	

	
	message_vision(HIG"$N����İ�"+ob->query("name")+HIG"���£���������ͷ��С�����һ���ʹܻ�������ȥ�ˡ�\n"NOR,me);
	destruct(ob);
//	me->delete_temp("sld/qushe");
//	me->delete_temp("sld");
	set("taskok",1);
	me->set_temp("sld/qushe/taskok",1);
	//��ǵ��ӳɹ�
	return 1;
}
