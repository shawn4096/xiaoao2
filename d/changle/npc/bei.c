// bei.c ����ʯ
// By River 2003.2.26
// ��ҪNPC.ɱ���� by spiderii@ty
// ͳһ�����㷨  by lsxk@hsbbs 2008/1/10

#include <ansi.h>
#include <job_mul.h>
#include <get_place.h>
inherit NPC;
#define XKX_QUEST1 "quest/������/Ħ����/"
#define XKX_QUEST2 "quest/������/������/"
//#define XKX_QUEST3 "quest/������/ѩɽ��Ե/"
//#define XKX_QUEST4 "quest/������/���͵�/"


string ask_job();
string ask_times();
string ask_finish();
string ask_fail();
string ask_xtling();

int check(object ob);

void create()
{
	set_name("����ʯ",({"bei haishi", "bei", "haishi"}));
	set("title", "���ְ��ܹ�");
	set("nickname",HIY"���ֻش�"NOR);
	set("long", "�����ǳ��ְ��ܹܣ��˳����ֻش��ı���ʯ��\n"+
		"����һ�����в��ݵ����ߡ�\n");
	set("age", 65);
	set("attitude", "friendly");
	set("shen", 0);
	set("str", 26);
	set("int", 29);
	set("con", 27);
	set("dex", 30);
	set("no_get", 1);
	set("no_bark", 1);
	set("job_npc", 1);
	set("no_ansuan", 1);

	set("max_qi", 34500);
	set("max_jing", 6200);
	set("eff_jingli", 8500);
	set("jiali", 220);
	set("combat_exp", 12500000); 
	set("unique", 1);

	set_skill("dodge",520);
	set_skill("force", 520);
	set_skill("literate", 300);
	set_skill("strike", 520);
	set_skill("kunlun-shenfa", 520);
	set_skill("banruo-zhang", 520);
	set_skill("shenzhao-jing", 520);
	set_skill("parry", 520);
	set_skill("medicine", 220);

	map_skill("force", "shenzhao-jing");
	map_skill("dodge", "kunlun-shenfa");
	map_skill("parry", "banruo-zhang");
	map_skill("strike", "banruo-zhang");
	prepare_skill("strike", "banruo-zhang");

	set("inquiry", ([
		"����"	:	(: ask_job :),
		"job"	:	(: ask_job :),
		"���"	:	(: ask_finish :),
		"finish":	(: ask_finish :),
		"����"	:	(: ask_times :),
		"����"	:	(: ask_fail :),
		"fangqi":	(: ask_fail :),
		"����"	:	"�����Ѿ�ʧ�ٶ��գ��������ڵ���Ѱ���С�",
		"���͵�":	"���Ҫ�Ȱ��������󣬲������顣",
		"������":	(: ask_xtling :),

		"���ְ�":	"���ְ��Ϊ�����á�ʨ���á������á������úͱ��������á�",
	]));

	setup();
	carry_object(ARMOR_D("changshan"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

string *party = ({"������","ʨ����","������","������","������"});

string ask_xtling()
{
	object me,bzling;
	me = this_player();
	
	if (!me->query(XKX_QUEST1+"over") 
		&& !present("bangzhu ling",me)
		&& !me->query_temp(XKX_QUEST1+"givebzling")
		&& me->query(XKX_QUEST1+"start"))
	{
		command("kick"+me->query("id"));
		command("say ���Ƿ��������������Ȼ���ˣ���ô���¶������ã����ܳ�ʲô���£�\n");
		command("say ����SOHU�����Ҵȱ�Ϊ���ķ��ϣ����ٸ���λ��ᣬ���Ҫ�պ��ˣ�\n");
		bzling=new("d/changle/obj/bangzhuling");
		bzling->set("owner",me->query("id"));
		bzling->move(me);
		me->set_temp(XKX_QUEST1+"givebzling",1);

		tell_object(me,HIC"����ʯ�ݸ���һ���������ƣ�\n"NOR);
		return "�ߣ���";
	}
	if (!me->query(XKX_QUEST1+"over"))
	{
		command("say ����Ϊ����°�ߣ��������ɰ��е����Ĵ���̽��\n");
		return "��";
	}
	
	if (time()-me->query("quest/������/time")<86400)
	{
		command("say ����Щ���ˣ�����������\n");
		return "��";
	}
	if (me->query("combat_exp")-me->query(XKX_QUEST1+"exp")<500000)
	{
		command("say ��͵���ˣ����书��ȥ���500k����ֵ������\n");
		return "������";
	}
	command("say ���������Ħ���ʿл�̿͵�����");
	command("say �ݽ�������,˭�õ���ö���л�̿Ϳ����������һ��Ը����Ҫ��");
	command("say ��Ϊл�̿��ڽ����������أ���ö������Ҳ����۱����ˡ�");
	command("say ������Ȼû�л��������Ｔ������һ׮�������յ����ˡ�");
	command("say ��ʮ��֮�ڼ������ˣ���Ҫ���汾�������ѣ����ȥ�ﱾ��õ���ö�����");
	command("say �ݰ��������̽����Ϣ����ö������п����������ͨ�����С�");
	command("say ����������������������֮�У���ȥ���Ұ���ö������������");
//	command("say ��Ҫ��ʹ���йٱʵĸ��֣���ҪС�ġ���");
	me->set_temp(XKX_QUEST2+"start",1);
	me->set(XKX_QUEST2+"start",1);
	me->set("quest/������/time",time());

	return "�ҵ�����Ϣ��©�������������գ���ȥ��أ�\n";

}

string ask_job()
{
	object me, ob, *living, target;
	string str, str2, address;
	object objwhere;
	int i,j;

	me = this_player();
	str2 = party[random(sizeof(party))];

	if (me->query_temp("changle/changle_job") && !me->query_temp("changle/job_place"))
		return "���������Բ��𣬵ص�������������������ɡ�";

	if (me->query_temp("changle/job_place1"))
		return "�㲻���Ѿ�֪���ˣ�ɱ���Ұ���ڵĳ�����"+me->query_temp("changle/job_place1")+CYN"һ�����ֹ���";

	if ( me->query_temp("changle/done"))
		return "�㲻���Ѿ���չ��һ���ز��ˣ����Ǽ���Ŭ���ɣ�";

	if (me->query_temp("changle/changle_job"))
		return "�Ҳ��Ǹ����������Ұ�������"+me->query_temp("changle/job_place")+CYN"����Ϯ�����㻹���Ͽ�ǰȥ��Ԯ��";

	if (me->query("job_name") =="���ְ�" && !wizardp(me))
		return "������곤�ְ����񣬻�����ȥ��Ϣһ��ɡ�";

	if (me->query("combat_exp") < 100000 )
		return "��λ" + RANK_D->query_respect(me) + "�书δ�ɣ��Ұﻹ����Ҫ��İ�����";

	if ( me->query_condition("job_busy"))
		return "�Ұ����ڱȽϿ��У���ʱ��û����������ȥ����";
	
	if(me->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		return "����������û�и���������㻹���ȴ����������������˵�ɡ�";

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (!j || j == sizeof(living) -1) continue;
		if(check(living[j]) ){
			target = living[j];
			objwhere = environment(target);
			str = objwhere->query("short");
			if (!sizeof(objwhere->query("exits"))
			|| str == "��ɮ��"
			|| str == "ɮ��"
			|| str == HIR"������"NOR
			|| str == "��շ�ħȦ" ) continue;
			if( get_place(base_name(environment(target))) != "" ) break;
		}
	}

	if( !target )
		return "��ʱû��������Ҫ�������һ��������ɡ�";

	ob = new(__DIR__"zhong");
	ob->set_temp("target", getuid(me));
	ob->set("title", HIR"���ְ�"+str2+"���°���"NOR);
	ob->move(objwhere);
	ob->set("env/invisibilty", 10);

	for ( j = 0; j < 5; j ++)
		ob->random_move();

	if ( environment(ob)->query("no_fight") || environment(ob)->query("quest") )
		ob->random_move();

	ob->delete("env/invisibilty");

	if (strsrch(file_name(environment(ob)), "/d/zhiye/") >= 0
	 || strsrch(file_name(environment(ob)), "/d/group/") >= 0) {
	 	if ( environment(ob)->query("outdoors"))
			me->set_temp("change/job_place", environment(ob)->query("outdoors")+environment(ob)->query("short"));
	 	else if ( environment(ob)->query("indoors"))
			me->set_temp("change/job_place", environment(ob)->query("indoors")+environment(ob)->query("short"));
		else me->set_temp("changle/job_place", environment(ob)->query("short"));
	}
	else me->set_temp("changle/job_place", get_place(base_name(environment(ob)))+environment(ob)->query("short"));

	if ( ! me->query_temp("changle/job_place"))
		return "��ʱû��������Ҫ������͹�һ��������ɡ�";

	address = strip(me->query_temp("changle/job_place"));
	me->set_temp("changle/changle_job",1);
	me->set_temp("changle/times", uptime());
	me->apply_condition("job_busy", 40 );
	me->set_temp("changle/npc_name", ob->name(1));
	command("bow "+ me->query("id"));
	command("whisper "+ me->query("id")+" �ҽӵ��ɸ봫�飬"+str2+"���°���"+ob->query("name")+"��"+ address +"������Ϯ������Ͽ�ǰȥ��Ԯ��");
	return "��λ"+RANK_D->query_respect(me)+"��Ϊ�Ұ�������������ʹ�����������͡�";
}

string ask_finish()
{
	object bzling;
	object ob, me = this_player();
	int gold,jobs,x,i,j;
	string msg;
	
	jobs=me->query("job_time/���ְ�");
	x=jobs % 50;

	if (!me->query_temp("changle"))
		return "�������û�����������ʲô����";

	if ( !me->query_temp("changle/done"))
		return "��������������ô��";

	msg = me->query_temp("changle/target_family");
	switch(me->query_temp("changle/done")){
		case 1:
            TASKREWARD_D->get_reward(me,"���ְ�",0,0,0,-3,0,0,0);
			msg = "��Ȼ�Ѿ�֪������"+msg+"��Ϊ���ߣ��������������ˡ�";
			//�����Ѿ��ں�����������
			//me->add("job_time/���ְ�", 1);
			//���ְ�1��������
			//jobs>2000 1m����,jobsΪ50�ı���
			if (random(jobs) > 2000 
				&& me->query("combat_exp")>1000000
				&& random(me->query("kar")) > 26
				&& x==0
				&& random(10)==2
				&& !me->query(XKX_QUEST1+"start")
				&& !me->query_temp(XKX_QUEST1+"start")
				&& !me->query(XKX_QUEST1+"over"))
			{
				command("look "+me->query("id"));
				command("say ���ַ��Ƽ�����䣬������Ӣ��˭�ս������ɧ?\n");
				message_vision(HIY"$N�Ӱ���̧��ͷ��������$nһ�ۣ�����˹���$n˵��������Ȼ�����Ŭ��Ϊ�������ǽ��ѣ��Ҿ���ʱ������Ϊ���о�Ӣ��������\n"+
									"�������ʯ����ΪĦ������л�̿����ӣ�������ܰѱ��������ȳ������ҳ��ְ�������ͣ�Ϊ�������ҵ�����\n"
									"���ȸ���һö��������,����һ����֪����·��С�ġ�\n\n"NOR,this_object(),me);

				me->set_temp(XKX_QUEST1+"start",1);
				me->set(XKX_QUEST1+"start",1);
				bzling=new("d/changle/obj/bangzhuling");
				bzling->set("owner",me->query("id"));
				me->set_temp("quest/������/time",time());
				bzling->set_temp(XKX_QUEST1+"start",1);
				bzling->move(me);

			}

			break;
		case 2:
            TASKREWARD_D->get_reward(me,"���ְ�",0,0,1,1,0,0,0);

			msg = "������ϧ�������д˼�������"+msg+"���Ұ������������ˡ�";
			//�����Ѿ��ں�����������
			//me->add("job_time/���ְ�", -1);
			break;
		case 3:
            TASKREWARD_D->get_reward(me,"���ְ�",0,0,1+random(1),4,0,0,0,this_object());
			gold = 1 +random(3);
			MONEY_D->pay_player(me, gold * 10000);
			msg = "���ĺã���Щ����"+RANK_D->query_respect(me)+"����ȥ�㻨���´λ���Ҫ����Ϊ�Ұ������";			
			break;
		default:
			msg = "�����������ˣ��뱨�濪����Ա��顣";
			//me->add("job_time/���ְ�", -1);
			break;
	}
		

	me->delete_temp("changle");
	me->clear_condition("job_busy");
	me->set("job_name", "���ְ�");
	if ( objectp(ob= present("cu bu", me)))
		destruct(ob);


	//tell_object(me,HIW"����������"+chinese_number(exp)+"�㾭�飬"+chinese_number(pot)+"��Ǳ�ܣ����Ѿ�Ϊ���ְ����"+chinese_number(me->query("job_time/���ְ�"))+"�Ρ�\n"NOR);

	return msg;
}

string ask_fail()
{
	object ob, me = this_player();
	int i;

	if (!me->query_temp("changle"))
		return "�������û�����������ʲô����";

	i = 40 - me->query_condition("job_busy");
	if ( i > 8 ) i = 8;
		me->apply_condition("job_busy", 9-i );

	if ( objectp(ob= present("cu bu", me)))
		destruct(ob);

	command("disapp "+ me->query("id"));
	me->delete_temp("changle");
	me->add("combat_exp", -(30+random(10)));
	return "��Ȼ���޷���ɣ���Ҳֻ������ˡ�";
}

string ask_times()
{
	object me = this_player();

	if ( !me->query("job_time/���ְ�"))
		return "��λ"+RANK_D->query_respect(me)+"����δΪ�����������";

	command("addoil "+ me->query("id"));
	return "��λ"+RANK_D->query_respect(me)+"�����Ѿ�Ϊ�������"+chinese_number(me->query("job_time/���ְ�"))+"���ˡ�";
}

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	 || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || !objectp(room=environment(ob))
	 || room->query("no_fight")
	 || room->query("outdoors") == "���ش��"
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/group/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/changle/") == 0
	 || strsrch(room_name, "/d/city/") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
  //          || strsrch(room_name, "/d/xiaoyao/") == 0
   //|| strsrch(room_name, "/d/quanzhen") == 0
   //|| strsrch(room_name, "/d/menggu/") == 0
   || strsrch(room_name, "/d/xiakedao/") == 0
   || strsrch(room_name, "/d/luoyang/") == 0    
   || strsrch(room_name, "/d/beijing/") == 0
         || strsrch(room_name, "/d/baituo/") == 0)
		return 0;
	return 1;
}

void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/changle/npc/bei");
		ob->move("/d/changle/xiaoting");
	}
	::die();
}

