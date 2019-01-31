// Room: /d/huashan/sheshen.c
// Date: Look 99/03/25
// add ������ by sohu
#include <ansi.h>
#define QUESTYT1 "quest/����������/��ɽ֮��/"
inherit ROOM;

int fight1(object me,object yinkexi,object xiaoxiang);

void create()
{
        set("short", "������");
 set("long", @LONG
����һ�μ�խ���յ�ɽ�£�����������ƣ�����Ԩ���޵ס��粻С�ģ�һ
ʧ�����ȥ��ֻ������ͷ���Ҳ�����
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "eastdown" : __DIR__"canglong",
 ]));

 set("no_die", 1);
        set("no_clean_up", 0);
        set("outdoors", "��ɽ" );

        set("coor/x",60);
  set("coor/y",50);
   set("coor/z",70);
   setup();
}
void init()
{
        object yinkexi,xiaoxiang;
		object me;
		me=this_player();
		//me->start_busy(2);
		if ((me->query_temp(QUESTYT1+"start")) && (!me->query(QUESTYT1+"over")))
		{
			if (!present("yin kexi",environment(me)))
			{
				yinkexi=new("d/kunlun/npc/yinkexi");
				yinkexi->move(environment(me));
			}
			if (!present("xiaoxiang zi",environment(me)))
			{
				xiaoxiang=new("d/kunlun/npc/xiaoxiangzi");
				xiaoxiang->move(environment(me));
			}
			call_out("fight1",0,me,yinkexi,xiaoxiang);

		}
		add_action("do_climb","climb");

}

int fight1(object me,object yinkexi,object xiaoxiang)
{
	
	
	
	
	message_vision(HIY"��Ȼ��Զ���Ż������������ˣ�һ����������������������һ�����������������ӣ���\n"+
		"������ֵ�������˾�Ȼ������˸�����ӡ��������������Ӽ��������ֳ����൱���ţ�\n"NOR,me);

		if (!objectp(yinkexi) || !objectp(xiaoxiang))  
{	
      call_out("fail",1,me);
     notify_fail("�ؼ���������������ʧ�ܡ�\n");
    
}



		
	yinkexi->add_temp("apply/dodge",200);
	yinkexi->add_temp("apply/parry",200);
	yinkexi->add_temp("apply/defense",200);
	xiaoxiang->add_temp("apply/dodge",200);
	xiaoxiang->add_temp("apply/parry",200);
	xiaoxiang->add_temp("apply/defense",200);
	//yinkexi->fight_ob(xiaoxiang);
	//xiaoxiang->fight_ob(yinkexi);
	message_vision(HIC"\n������˵���������֣��⻪ɽ����ɽ�ܣ��������Բ������ǺúõĶ��ϼ��գ� \n����ͺ¿��ͨ��ι��Ҳδ����Ѱ�õ������������Ѱ�ң������� ����ȥ����"NOR,me);
	message_vision(HIG"\n������������˵������������Īϲ������ͺ¿����Ѱ���ǲ��ţ���Ȼ����ɽ�¿׵�֮����\n��������óȻ��ȥ������ײ�������������\n"NOR,me);
	message_vision(HIC"\n��������������������ıԶ�ǣ����Բ��ȴ��֪�кθ߼�����\n"NOR,me);
	message_vision(HIG"\n�����ӵ�����������ɽ���¹����࣬���Ǳ��һ����Ƨ�ģ����������Ǻ��� ���ǵ�ʿ��\n���������ˣ�ռ���¹ۣ�����ôס��ȥ����������ͺ¿�����벻�����ǻ���ɽ���������µ�ͣ����\n���ٲ����ģ���ɽ����Ѱ���飬��ɽ���غ����£�Ҳ��ȥ�ˡ���\n"NOR,me);
	message_vision(HIC"\n������ϲ�����������ִ˼ƴ����\n������æ��������������\n"NOR,me);
	
	me->set(QUESTYT1+"start",1);
	
	call_out("jueyuan_come",2+random(3),me,yinkexi,xiaoxiang);
	return 1;
}
int jueyuan_come(object me,object yinkexi,object xiaoxiang)
{
	object jueyuan;
	if (!objectp(jueyuan=present("jueyuan dashi",environment(me))))
	{
		jueyuan=new("d/shaolin/npc/jueyuan");
		jueyuan->move(environment(me));
	}
	message_vision(HIY"������ɽ����$n�ȵ��������鲻������λ���ѣ�����������������������ֻ�����ɽ���죬\n������������֮�����䲻���͸߰���������֮�������ǲ�����\n"NOR,me,jueyuan);

	message_vision(HIY"\n$Nһ�������룺�����Ͼ���������һλ���֣���ȴ��֪����$N����̽������������������ȥ��\n�¹���ֻ��һ����ӰѸ�����׵ı���ɽ��������һ�ᣬ�������Ӱ�й������ˣ�һ������ɮ�ˣ�Я��һ�����ꡣ��\n"NOR,me);
	message_vision(HIY"\n�������������Ӷ��������ڳ��ݴ��У�������Ҳ����͸һ������\n"NOR,me);
	message_vision(HIY"\n��$n�����߸���������������������졢�����˵��ټ������������弲����ȥ��\n"NOR,me,jueyuan);
	message_vision(HIC"\n�ۼ���$n��ȻҪ·����ȥ�������ĺ���һ����"HIR"����yell��"HIC"���ǲ�����",me,jueyuan);
	add_action("do_yell","yell");
	me->delete_temp(QUESTYT1+"start");
    return 1;

}

int do_yell(string arg)
{
	object me;
	me=this_player();
	if (!arg||!me->query(QUESTYT1+"start")) return notify_fail("�����ɽҰ��ģ���Ϲ��ʲô��");
	if (arg=="��Զ��ʦ")
	{
		message_vision(HIC"$N��æ��Զ���ľ�Զ���к�������ι����Զ���У������˱��ڴ˴�����\n"NOR,me);
		message_vision(HIB"�������䣬��ȻԶ����������Ϯ������������Ȼ���졢��������ɱ����ڣ�\n"NOR,me);

		if (random(me->query_skill("dodge",1))<200)
		{
			message_vision(HIR"$N��С�ı��������У�\n"NOR,me);
			me->receive_wound("qi",-random(3000),"������");
			return 1;
		}else {
			message_vision(HIG"$N������ֲ�������İ�����Ȼ�������ڹ���Զ��������\n"NOR,me);
			me->set(QUESTYT1+"yelljueyuan",1);
			return 1;
		}

	}
	if (arg=="��Եǧ�������,��Ե���治���!" )
	{
		if (!me->query(QUESTYT1+"yelljueyuan")) return notify_fail("���Զ������������Եǧ�������,��Ե���治���!��\n");
		
		message_vision(HIC"$N����������Զ���ľ�Զ�������ֺ���������Եǧ�������,��Ե���治��꣡��\n"NOR,me);
		message_vision(HIY"\n\n�Ǿ�Զ����������ɽ��֮�䣬��ʱͣ������ͷ˵���� �����͸���ָ���Խ򡣡���\n"NOR,me);
		me->set(QUESTYT1+"yellyouyuan",1);
		return 1;
	}
	if (arg=="̤����Ь���ٴ�,����ȫ���ѹ���!" )
	{
		if (!me->query(QUESTYT1+"yellyouyuan")) return notify_fail("���Զ������������Եǧ�������,��Ե���治���!��\n");

		message_vision(HIC"$N����������Զ���ľ�Զ�������ֺ�������̤����Ь���ٴ�,����ȫ���ѹ���!��\n"NOR,me);
		message_vision(HIY"\n\n�Ǿ�Զ���д�ϲ��Я��������ɲ����أ�\n"NOR,me);
		me->set(QUESTYT1+"yelltiexie",1);
		message_vision(HIG"\n\n�����Ӻ�����������$N�ĳ���֮������һ����ͬС�ɣ��໥ʹ����ɫ���Ӳݴ��д��˳������򶫱㱼��\n"NOR,me);
		message_vision(HIC"$Nһ�����ã�����������ߣ�����"HIR"����(zulan)"HIC"���ǲ�������\n"NOR,me);
		add_action("do_zulan","zulan");
		return 1;
	}
}

int do_zulan()
{
	object me,yinkexi,xiaoxiang;
	int zulan;
	me=this_player();
	me->start_busy(1);
	me->set("quest/����������/��ɽ֮��/time",time());
	if (!me->query(QUESTYT1+"yelltiexie")) return notify_fail("����Ե�޹ʣ�Ҫ����ʲô��");
	//if (me->query(QUESTYT1+"zulan")-zulan>1) return notify_fail("���Ѿ�������һ����,�´�������\n");
	if (time()-me->query("quest/����������/time")<86400)
		return notify_fail("������̫�ڿ��ˣ�����������\n");

	if (!objectp(yinkexi=present("yin kexi",environment(me))))
	{
		yinkexi=new("d/kunlun/npc/yinkexi");
		yinkexi->move(environment(me));
	}
	if (!objectp(xiaoxiang=present("xiaoxiang zi",environment(me))))
	{
		xiaoxiang=new("d/kunlun/npc/xiaoxiangzi");
		xiaoxiang->move(environment(me));
	}
	zulan=me->query(QUESTYT1+"zulan");
	me->add(QUESTYT1+"zulan",1);
	
	yinkexi->kill_ob(me);
	//me->fight_ob(yinkexi);
	xiaoxiang->kill_ob(me);
	//me->fight_ob(xiaoxiang);
	call_out("fight_over",10+random(5),me,yinkexi,xiaoxiang);
	return 1;
}

int fight_over(object me,object yinkexi,object xiaoxiang)
{
	
	
	if (!me) return 1;
	if (!yinkexi)
	{
		tell_object(me,YEL"��ʧ��ɱ�������������޷���ɺ�������ɽ�������ڣ�����ʧ�ܣ�\n"NOR);
		call_out("fail",1,me);
		return 1;
	}
	if (!xiaoxiang)
	{
		tell_object(me,YEL"��ʧ��ɱ���������ӣ��޷���ɺ�������ɽ�������ڣ�����ʧ�ܣ�\n"NOR);
		call_out("fail",1,me);
		return 1;
	}
	if (!objectp(present("jueyuan dashi",environment(me))))
	{
		tell_object(me,YEL"��Զ��ʦ���ٸô����޷���ɺ������ֻ��ڣ�����ʧ�ܣ�\n"NOR);
		call_out("fail",1,me);
		return 1;
	}
	if (!me->is_fighting())
	{
		tell_object(me,YEL"�㴦�ò�����ʹ��ս��û�������Զ��ʦ��ָ�㣬����ʧ�ܣ���\n"NOR);
		call_out("fail",1,me);
		return 1;

	}
	message_vision(CYN"��Զ��ʦ��������$N�ѵ�����ʹ�á���ͨ�˴����¹��˭�֡����������ø���������ô��\n"NOR,me);
	tell_object(me,WHT"�ھ�Զ��ʦ��ָ���£��㾭����ս�����ڴ��������λ�������ޣ�\n"NOR);
	
	yinkexi->apply_condition("neishang",10);
	yinkexi->remove_target();
	xiaoxiang->apply_condition("neishang",10);
	xiaoxiang->remove_target();

	tell_object(me,WHT"����������ڵز�������������\n"NOR);
	tell_object(me,WHT"�ھ�Զ��ʦ��������ʾ�£��㽫�����������ȴû�з����κξ�Զ��ʦ��˵�ľ��飡\n"NOR);
	tell_object(me,HIY"ֻ��������ֵ��ǣ��������ߵ���ֻ��˶�Ĵ����ȴ��Щ�ͳ�������������\n"NOR);

	call_out("leave",3+random(5),me,yinkexi,xiaoxiang);
	return 1;

}

int leave(object me,object yinkexi,object xiaoxiang)
{
	object jueyuan;
	if (objectp(jueyuan=present("jueyuan dashi",environment(me))))
		destruct(jueyuan);
	if (objectp(yinkexi=present("yin kexi",environment(me))))
		destruct(yinkexi);
	if (objectp(xiaoxiang=present("xiaoxiang zi",environment(me))))
		destruct(xiaoxiang);
	message_vision(HIC"�ۼ���Զ�������ᵽ����û���ѵ������Ƕ������ȥ��\n"+
		"�������������Ӷ������ڵ����������ѣ�������ɱ�˶��ˣ���ȴ�ֲ������ġ�\n"NOR,me);
	message_vision(HIG"\n\n\n��ʱ�����������������໥���֣��������Ƕ�ȥ��\n"NOR,me);
	
	if (me->query(QUESTYT1+"over")) return 1;
	
	me->set(QUESTYT1+"over",1);
	me->set("quest/����������/time",time());
	me->set("quest/����������/combat_exp",me->query("combat_exp"));
	me->delete_temp(QUESTYT1+"start");
	log_file("quest/YTTLJ", sprintf("%s(%s) ˳���⿪<<����������>>�е�һ�½ڻ�ɽ֮�ۣ��ܹ�ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query(QUESTYT1+"fail"),
          me->query("kar"),
          me->query("combat_exp")) );

	tell_object(me,HBBLU+HIW"\n\n\����������֮��һ�½ڡ���ɽ֮�ۡ�ƪ������\n"NOR);
	//me->add("combat_exp",);
	return 1;
}
int fail(object me)
{
	if (!me) return 1;
	me->add(QUESTYT1+"fail",1);
	me->set("quest/����������/time",time());
	me->set(QUESTYT1+"combat_exp",me->query("combat_exp"));
	me->delete_temp(QUESTYT1+"start");
	me->delete(QUESTYT1+"start");
	log_file("quest/YTTLJ", sprintf("%s(%s) ����<<����������>>�е�һ�½ڻ�ɽ֮�ۻ���ʧ��%d�Ρ���Դ��%d�����飺%d��\n",   
          me->name(1),
          me->query("id"), 
          me->query(QUESTYT1+"fail"),
          me->query("kar"),
          me->query("combat_exp")) );
	return 1;
	
}

int do_climb(string arg)
{
        object me = this_player();
        int time;
	
		if (me->query("oyf/hamagong") == 2)
		{
			time = time() - me->query("quest/hama/nizhuan/time");
		}else if (me->query_temp("wugou/askguo"))
		{
			time = time() - me->query("quest/gb/dgb/wugou/time");
		}
				
        if (arg!="up") 
			return notify_fail(HIG"�������û�취����\n"NOR);

        if (me->query_skill("dodge",1) < 450)
			return notify_fail(HIG"������Ṧ����450�����˰�����޽�չ�����ǻ�ȥ�����Ṧ�����ɡ�\n"NOR);
        
        
        if (me->query("oyf/hamagong") < 2 && !me->query_temp("wugou/askguo"))
			return notify_fail(HIG"��Ȳ���ؤ����ӣ��ֲ��Ǹ�󡹦���ˣ��������������İɡ�\n"NOR);     

        if (me->query("oyf/hamagong") == 3 || me->query("quest/gb/dgb/wugou/pass"))
			return notify_fail(HIG"��ɽ�������������Ѿ��⿪�ˣ����������ˡ�\n"NOR);     

/*	 if (me->query("quest/jiebai/super") >=3 && me->query("registered") < 3)
        return notify_fail(HIG"���常�����˶����ˣ���Ҫ�������ĵ��ˡ�\n"NOR);  
*/
      
		if ( time < 86400 )
	
        return notify_fail(HIG"������̫����Щ�ɡ�\n"NOR);  
        if ( me->query("combat_exp") < 6000000 ) 
        return notify_fail(HIG"�㾭�鲻��6m,����Ҳû���á�\n"NOR);  
        
        if (me->query("jingli") < 1500)
        return notify_fail(HIG"�㾫����1500������ЪЪ�����ɣ�С������С����\n"NOR);

        me->add("jingli",-500);

        message_vision(HIG"$N�ֽŲ��ã�ʹ���˳��̵�������������������\n"NOR,me);
        me->move("/d/huashan/hamasuperquest/jueding1");
        return 1;
}

