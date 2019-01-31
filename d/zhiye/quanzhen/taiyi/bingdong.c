//Cracked by Kafei
// road: /d/zhongnan/bingdong.c
// by sdong 08/98

#include <ansi.h>
#include <room.h>
inherit ROOM;
private int blow_result(object victim);
int blow();
int do_dig();
void setup_ob(object me,object victim);

void create()
{
		  set("short",WHT"����"NOR);

		  set("long",@LONG
������ָ��ֿ���������Ȼ�����ҵģ����ں������ˣ����Ͻ��ź��ļ����
����Ķ���Щ������
LONG);

		  set("exits",([
				"east": __DIR__"xuanya4",
							 ])
			  );
	  set("cost",1);
	  setup();
}

void init()
{
	add_action("do_dig", "dig");
	remove_call_out("blow");
	call_out("blow",4 + random(3) );
}

int do_dig()
{
	remove_call_out("blow");
	call_out("blow",1 );
	return 1;
}

int blow()
{
	object *inv = all_inventory(find_object(__DIR__"bingdong"));
	object ob, me= this_player();
	int i;

	if( !this_player() || !environment(this_player()) )  return 1;
	if( base_name(environment(this_player())) != __DIR__"bingdong") return 1;

	message_vision( HIW"\n�����һ������������ȫ���ѪҺ���춳���ˣ�\n"NOR, this_player() );

	for ( i=0 ; i < sizeof(inv); i++)
	{
		if ( (string)inv[i]->query("race") == "����" )
		{
			blow_result(inv[i]);
		}
	}
	

	remove_call_out("blow");
	call_out( "blow",4 + random(3) );
	return 1;
}

private int blow_result(object victim)
{
	object ob2;

	if( random(60)==1 )
	{
		ob2=new(__DIR__"bigtiger");
		ob2->move(environment(victim));
		message_vision(HIR"ͻȻ�Ӷ������߽�һֻ$N�����������ˣ�ŭ��һ���������Ƶ���$n���������\n"NOR, ob2,victim);
		setup_ob(ob2,victim);
		ob2->kill_ob(victim);
		ob2->add_temp("offenders/"+victim->query("id"), 1);
		ob2->start_busy(1+random(3));
		victim->kill_ob(ob2);
	}

	if( random( victim->query_skill("force") ) > 45 && victim->query("neili") > 20 )
	{
		message_vision( HIC"\n$N�Ͻ��˹�������\n"NOR, victim );
		victim->add_temp("xtg/yungong",1);
		if( victim->query_skill("force",1) < 350 )
			victim->improve_skill( "force",victim->query("con")+10 );
		victim->add("neili",-random(40));
		//�����������,һ��һ��
		if (random(victim->query_temp("xtg/yungong"))>20
			&&victim->query_temp("quest/qz/xtg/wuqi/askhao")
			&&victim->query("quest/qz/xtg/wuqi/start")
			&&(time()-victim->query("quest/qz/xtg/wuqi/time"))>86400)
		{
			remove_call_out("xtg_effect");
			call_out("xtg_effect",1,victim);
			victim->delete_temp("qest/xtg/askkma");
		}
	}
	else
	{
		message_vision( HBWHT"\n$N�����ش��˸������\n"NOR, victim );
		victim->receive_wound("qi", random(300));
		victim->receive_damage("qi", random(500));
		if( victim->query_skill("force",1) < 300 )
			victim->improve_skill( "force",victim->query("con")*victim->query("int") );
	}


	return 1;
}

int xtg_effect(object me)
{
	int i,j,k;
    if (!me) return 0;
 
	i=random(me->query("kar"));
	if (me->query("marry"))
	{
		k=4;
	}else k=0;

	message_vision(HIC"���ҵĺ�������������裬�������������칦��ʱ��Ȼ��Ϊһ��ů���ڵ��������鲼$N����!\n"NOR,me);
	j = 20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);

    if (me->query("kar")>30) 
    {
	  log_file("quest/bug", sprintf("%s(%s) �������칦������Ԫʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
    }
	if (i>27
		&& j<3
	   	&& random(me->query("con"))>(40+k)
		&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\nһ��ů������β�̣�˳�������ϣ�����ٻ�Ѩ���������á�\n"
		 +"Ȼ���Ȼ���£������������������ڵ�����Ʋ�����\n"+
			 " $N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n$N�������������������������칦������Ԫ�İ��أ����칦��Ȼ��ͨ����\n"NOR,me); 
		 message_vision(HIG"\n��ϲ������$Nǧ����࣬���ڵó���Ը���⿪���칦������Ԫ���ռ����⣡��\n"NOR,me); 

         log_file("quest/xtgwqcy", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ��������칦������Ԫ�İ��أ���ǰ�������ֵ��%d,��ǰ���ֵ��%d,��ǰ����ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/qz/xtg/wuqi/fail"),
		 i,
		 j,
		 me->query("con"),
         me->query("combat_exp")));

		 me->set("quest/qz/xtg/wuqi/time",time());
		 me->set("quest/qz/xtg/wuqi/pass",1);
		 me->delete_temp("quest/xtg");
		 me->delete_temp("xtg");
		 me->start_busy(1);
		 me->set("title",HIC"���칦"+HIR" ������Ԫ"NOR);
		 me->add("mytitle",HIC"���칦"+HIR" ������Ԫ"NOR);

		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N�������Σ��ڹ������·�����һ�����,�޷�ͻ�ơ�\n"NOR,me); 
		 message_vision(HIY"\nû������͸��������Ԫ�����������\n"NOR,me); 
		 me->apply_condition("snake_poison",1);
		 message_vision(HIY"\n�������칦������Ԫ��������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xtgwqcy", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ������칦������Ԫ��������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/qz/xtg/wuqi/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/qz/xtg/wuqi/fail",1);
		 me->set("quest/qz/xtg/wuqi/time",time());
		 me->delete_temp("quest/xtg");
		 me->delete_temp("xtg");

		 me->start_busy(1);
		 return 1;
   }

}

//��������
void setup_ob(object me,object victim)
{
	object *inv;
	mapping skill_status;
	string *sname;
	int i, max = 0, max1, j;


	if ( !me->query_temp("copied") ) {
		if ( mapp(skill_status = victim->query_skills()) ) {
		skill_status = victim->query_skills();
		sname = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			if ( skill_status[sname[i]] > max ) max = skill_status[sname[i]];
		}


		max1 = (int)max + random(max*3);

		if( victim->query("combat_exp",1) < 10000 ) max1 = max1/2;
		me->set_skill("dodge", max1);
		me->set_skill("parry", max1 );
		me->set_skill("force", max1);
		me->set_skill("strike", max1);
		me->set_skill("cuff", max1);
		me->set_skill("claw", max1);
		me->set_skill("force", max1);
		me->set_skill("yinyun-ziqi", max1);
		me->map_skill("force", "yinyun-ziqi");


		me->set("combat_exp", victim->query("combat_exp",1)+random(victim->query("combat_exp",1)/2));

		me->set("max_qi", victim->query("max_qi"));
		me->set("eff_qi", victim->query("max_qi"));
		me->set("max_jing", victim->query("max_jing"));
		me->set("eff_jing", victim->query("max_jing"));
		me->set("max_jingli", victim->query("max_jingli"));
		me->set("eff_jingli", victim->query("max_jingli"));

		me->set("qi", me->query("max_qi"));
		me->set("max_neili", victim->query("max_neili") );
		me->set("neili", victim->query("neili") );
		me->set("jing", me->query("max_jing"));
		me->set("jiali", victim->query("jiali")*3/4);
		if ( victim->query("max_jing") > 0 ) {
			me->set("max_jing", victim->query("max_jing"));
		}
		else me->set("max_jing", 500);
		me->set("jing", me->query("max_jing"));

		me->set("no_sing", 1);
		me->set_temp("copied", 1);
		me->set_temp("apply/attack", 80);
		me->set_temp("apply/damage", victim->query_temp("apply/damage") );
		}
	}
}
