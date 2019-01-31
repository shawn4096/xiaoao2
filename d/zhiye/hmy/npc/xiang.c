// xiang.c ������
// Finish by action@SJ 2009.1.6
//�����¼���������ϵ����£ͬ����߻�ɱ������ by renlai
#include <ansi.h>
#include <job_mul.h>
#include <get_place.h>

inherit NPC;
inherit F_MASTER;

int check(object ob);

int ask_jiuwen();
string do_ask();
string do_cancel();
string do_finish();
int is_target(object corpse, object me);

void create()
{
        set_name("������", ({ "xiang wentian", "xiang", "wentian"}));
        set("long", "ֻ������ò���ݣ����θߴ������������һ�Ի��׳��룬������ǰ��\n"+
		"���ϸ���һ���������ٿ�������ʱ��ȴ���䵶��\n");
        set("title",HIY"������� "HIW"������ʹ"NOR);
        set("gender", "����");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 4000);
        set("max_jing", 5200);
        set("eff_jingli", 5500);
        set("jiali", 200);
        set("combat_exp", 10400000);

        set_skill("strike", 460);
        set_skill("blade", 220);
        set_skill("club", 460);
        set_skill("parry", 460);
        set_skill("dodge", 460);
        set_skill("force", 460);
        set_skill("literate", 160);

        set_skill("tianmo-gun",460);
        set_skill("tianmo-zhang",460);
        set_skill("tianmo-dao",200);
        set_skill("huanmo-wubu",460);
        set_skill("tianmo-gong",460);
        set_skill("tianmo-jue",200);

        map_skill("force", "tianmo-gong");
        map_skill("parry", "tianmo-gun");
        map_skill("blade", "tianmo-dao");
        map_skill("club", "tianmo-gun");
        map_skill("dodge", "huanmo-wubu");
        map_skill("strike", "tianmo-zhang");

        prepare_skill("strike", "tianmo-zhang");
        set("inquiry", ([
                 //"����" : (: ask_mimi :),
		         "����" : (: ask_jiuwen:),
			     //"��Գ��ħ" : (: ask_jinyuan:),
				 "job": (: do_ask() :),
                "����": (: do_ask() :),
				"fangqi": (: do_cancel() :),
                "cancel": (: do_cancel() :),
                "����": (: do_cancel() :),
				"���": (: do_finish() :),
				"finish": (: do_finish() :),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
		        "����������ƺ�������һ��ڣ��������þƣ���\n",
					"������������������ߺߣ�÷ׯ����....�Ķ�����������ʲô�����أ���\n",
					"������������������������С���е���˼����\n",
					"�������������������ϧ��������ʮ����Χ����ɽ��һȥ���أ����׷����˺��£�����\n",
					"����������������������µĺ����似��ʧ���٣������������϶��ĺ��аԵ�����\n",
        }));
        create_family("�������", 6, "����");
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "club.luanwu" :),
				(: perform_action, "club.zhenfeng" :),
                (: exert_function, "tianmo" :),
        }));
		
        setup();

        carry_object(MISC_D("cloth"))->wear();  
        carry_object(BINGQI_D("club"))->wield();      
}

void init()
{
	//object ob;
	//ob = this_player();

	::init();
	/*
	if( interactive(ob = this_player()) && !is_fighting() && !is_busy()	  
	   && ob->query_temp("ry/ry_job/��")) {
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}*/
}

/*
void greeting(object me)
{
	object target, ob;
	mapping quest;

	if( !me || environment(me) != environment() || !living(me)) return;

	if (!me->query_temp("ry/ry_job") || !me->query_temp("ry/ry_job/��") || !stringp(me->query_temp("ry/npc/id"))) return;

	command("nod "+me->query("id"));

	ob = this_object();

	if(objectp(target=present(me->query_temp("ry/npc/id"), environment(me)))
	  && target->query_temp("riyue_job") == me
	  && living(target)){
		me->add_busy(2);
		target->set_leader(0);
		command("haha");
		command("touch "+target->query("id"));
		command("say "+target->name()+"�������Ҿȳ��ν����ֶ���һ�ݰ��գ�������");
		write("������˳�ֵݸ�"+target->name()+"һ��ҩ�衣\n");
		call_out("done", 2, target, me, quest, 1);
		return;
	}	
}
*/


string do_finish()
{
	object me, ob,target;
	me = this_player();
	ob = this_object();
	
	if (!me->query_temp("ry/ry_job") || !me->query_temp("ry/ry_job/��") || !stringp(me->query_temp("ry/npc/id"))) 
		return "��û��������Ҫ���ʲô��";
	
	if(objectp(target=present(me->query_temp("ry/npc/id"), environment(me)))
	  && target->query_temp("riyue_job") == me
	  && living(target)){
		me->add_busy(2);
		target->set_leader(0);
		command("haha");
		command("touch "+target->query("id"));
		command("say "+target->name()+"�������Ҿȳ��ν����ֶ���һ�ݰ��գ�������");
		 message_vision("\n$N˳�ֵݸ�$nһ��ҩ�衣\n",ob,target);
		//write("������˳�ֵݸ�"+target->name()+"һ��ҩ�衣\n");
		call_out("done", 1, target, me, 1);
		return "�����ĺܺá�";
	}	
}


string do_ask()
{
	object me, ob,target, *living;
	string type, t;
	mapping quest;
	int i,j;
	string str;

	me = this_player();
	ob = this_object();

	if(ob->is_busy()) return "����æ���أ���ȵȡ�";	

	if( me->query("combat_exp") < 1000000
	 || me->query("shen") > -1000)
	return RANK_D->query_respect(ob)+"������������,�ֲ����ĺ��ֺݣ����ܷ�������ȥ������أ�";

	if( me->query("job_name") == "���¸���")
		return "��հ���ң�������Ϣһ�°ɡ�";	

	if( me->query_condition("job_busy"))
		return "����æ���أ���";

	if(me->query_condition("riyue_job"))
		return "���ϴε����¸�������û����ɰɡ�";

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		if(check(living[j]) ){
			target = living[j];
			str = environment(target)->query("short");
			if( str == "��ɮ��"
			 || str == HIR"������"NOR
			 || str == "��շ�ħȦ"
			 || environment(target)->query("quest")
			 || str == HIB"����Ժ"NOR) continue;
			if( get_place(base_name(environment(target)))!="" )
				break;
		}
	}
	
	if( !target )
		return "����ȽϿ��У����һ��������ɡ�";	
	
	me->apply_condition("job_busy", 30);
	me->apply_condition("riyue_job", 30);
	me->delete_temp("ry/qing");//�����ۼ�
	me->set_temp("ry/ry_job",1);
	me->set_temp("ry/times", uptime());
	me->set_temp("ry/npc",1);
	me->set_temp("ry/npc_time",time());
	me->set_temp("ry/npc_place",get_place(base_name(environment(target)))+environment(target)->query("short"));
	
	ob=new(__DIR__"robber");
	
	ob->setparty(10,me->query("max_pot")-100,me->query("combat_exp"));	
	
	//����ӽ�ȥ״̬
	ob->copy_player(me);//�ȳ�ʼ��npc��Ѫ���������һ�»���	
	ob->set_temp("target", me->query("id"));
	ob->move(environment(target));
	//ob->add_temp("apply/defense", 300);
	//ob->add_temp("apply/armor", 300);
	//ob->add_temp("apply/damage", 1000);
	
	me->set_temp("ry/npc_ob",ob);
	me->set_temp("ry/npc/name",ob->query("name"));
	me->set_temp("ry/npc/id",ob->query("id"));
	
	type = random(2)?"��":"ɱ";
	
	if(type == "ɱ"){
		me->set_temp("ry/ry_job/ɱ",1);		
		command("grin");
		command("whisper "+me->query("id")+" �����ţ��е��ӻر�"HIR+ob->query("title")+ob->query("name")+CYN"�������ڶ������ܣ���ô����");
		return "�ٺ٣�����"HIY+me->query_temp("ry/npc_place")+CYN"һ������ȥ����ɱ�˴�������ʬ��ϻ�����\n";
	}
	else{
		me->set_temp("ry/ry_job/��",1);		
		command("nod");
		command("whisper "+me->query("id")+" ���ˣ�"HIG+ob->query("title")+ob->query("name")+CYN"���ҽ��鲻��������������ȳ��ν���֮�¼�ֱ���練�ơ�");
		return "��ʹ�����ȥ"HIY+me->query_temp("ry/npc_place")+CYN"��������";
	}
}


int accept_object(object who, object ob,object me)
{
       int type,count,exp,pot,total_job_times;
       me=this_object();
	   
	    if(ob->query("id") == "heimu ling") 
		{
			if (!who->query_temp("hssb/askxiang")) {
	                 command("say ����������ʲô��\n");	
		        return 0;
               }
			 if (who->query_temp("hostage/linggived"))
	    {	
		
		who->delete_temp("hostage/linggived");
		write(HIY"�����콫����ľ���������з�����ȥ�Ŀ��š�\n"NOR);
        write(CYN"���������Ķ���������������������ϲ���ǡ�\n"NOR);
		
		command("say ��Ȼ�������ҵ�������ľ����ҾͰ������Ϣ�����㡣\n");
		command("say ʮ����Χ����ɽһȥ���أ��һ����������˶Է��ļ�ơ�\n");
		command("say Ҳ��˵�������ȥ��ɽ��ɽ����ת��ת��˵������ʲô���˵ķ��֡�\n");
		command("say ���������������������죬�ҿ��㻹����Ե�ĺá����²���ǿ��\n");
		who->set_temp("hssb/juejiasked",1);
		destruct(ob);
		return 1;
	         }
			 else {
               command("say ��Ϲ����ʲô��\n");
	     return 0;
	}			
			
		}
		else
		{
       
       type = is_target(ob, who);
       switch (type){
	    case 0: command("say ���ø�"+ob->name()+"���Ҹ��");
		    return 0;
	    case -1:command("say Ү���������㲻ȥ����ɱ�˶���ȥ�ˣ�������");
		    return 0;
	    case -2:command("say �ٺ٣�˭����ȥ��ɱ���ˣ���ֱ�Ǹ����������Ĩ�ڣ�");
		    who->apply_condition("job_busy", 9);
		    return 0;
	    case -3:command("say �ţ����˲�����ɱ�ģ�");
		    who->apply_condition("job_busy", 9);
		    return 0;
	    case -4:command("say Ŷ�����Ǹ�ͬ��ͬ�Ե��ˣ�������ù�ɣ�");
		    return 0;
	    default:command("haha");
		   command("say �ã��ã�����²����ǿ�����ӡ�");
		   message_vision("\n$N��$n����һЩ��ѧ�ϵ����ѣ�$n������˼�ص���ͷ��\n",me, who);		   
		TASKREWARD_D->get_reward(who,"���¸���",-1,0,0,10+random(6),0,0,0,"������"); 

    log_file("job/fuxing",sprintf("%8s%-10s��ɵ�%4d�����¸���ɱ�����񣬾��飺%d\n",who->name(),"("+who->query("id")+")",who->query("job_time/���¸���"),who->query("combat_exp")),who);
	
    who->clear_condition("job_busy");
	who->clear_condition("riyue_job");
    //who->apply_condition("riyue_job", 3);
	who->delete_temp("ry");
	who->delete_temp("riyue_job");
	
	
	if (who->query("family/family_name")=="�������" && !who->query_temp("mz_entrance") && !who->query("quest/xxdf/pass") && who->query("combat_exp")>8000000 )	
		{
			if (QUEST_D->job_questing(who,2,"mz_entrance","���¸���",4000,"ѩɽ",4000,"mz_entrance"))
		     command("say "+who->query("name")+"����˵����÷ׯ��λׯ��ϲ�������黭��������Ͷ��������ȥ����������һ����Ե��\n");	
		}	
	/*
	total_job_times=who->query("job_time/���¸���")+who->query("job_time/ѩɽ");
	
	if (wizardp(who)||
	(random(who->query("job_time/���¸���"))>4000 
	   && random(who->query("kar"))>25 
	   && random(who->query("job_time/ѩɽ"))>4000 
	   && who->query("family/family_name")=="�������"
	   && !who->query_temp("mz_entrance")
	   && !who->query("quest/xxdf/pass")
	   && who->query("combat_exp")>8000000
	   && random(10)<5
	   && total_job_times % 50 == 0 ))
	{
		who->set_temp("mz_entrance", 1);
		command("say "+who->query("name")+"����˵����÷ׯ��λׯ��ϲ�������黭��������Ͷ��������ȥ����������һ����Ե��\n");
		log_file("quest/xixing",sprintf("%8s%-10s���¸�������ʱ��ȥ÷ׯ�����£�%4d��ѩɽ��%4d������%2d��\n",who->name(),"("+who->query("id")+")",who->query("job_time/���¸���"),who->query("job_time/ѩɽ"), who->query("kar")),who);
	}   
*/
	
	who->set("job_name", "���¸���");	
	call_out("destroy", 1, ob);
	return 1;
	    }
      return 1;
		}
}


int is_target(object corpse, object me)
{
	if (!me->query_temp("ry/ry_job")) return 0; // didnt get the job	

	if (!me->query_temp("ry/ry_job/ɱ")) return -1;  // job type is not killing

	if ( corpse->query("id") != "corpse" && corpse->query("id") != "shouji") return 0;// it's not a corpse or head.
	
	if (corpse->query("kill_by") != me) return -3;

	if ( corpse->query("victim_id") != me->query_temp("ry/npc/id") || corpse->query("victim_name") != me->query_temp("ry/npc/name"))
		return -2;      // killed wrong person.
	if ( corpse->query("victim_user")) return -4;   // killed a player.
	else return 1;
	
}


void destroy(object ob)
{
	destruct(ob);
}

string do_cancel()
{
	object me;
	int exp, i;

	me = this_player();
	exp = me->query("combat_exp");

	if(!me->query_temp("ry/ry_job"))
		return "��û�������񣬺�������ʲô��";

	me->add("combat_exp",-(20+random(50)));
	if(exp > 500000){
	      me->add("combat_exp",-(30+random(40)));
	}
	i = 40 - me->query_condition("job_busy");
	if ( i >= 9 )
		me->apply_condition("job_busy", 1);
	else
		me->apply_condition("job_busy", 9 - i);
	//me->clear_condition("riyue_job");
	me->apply_condition("riyue_job", 10);
	me->delete_temp("riyue_job");
	
	if (me->query_temp("ry/npc_ob")) 
	 {
		 destruct(me->query_temp("ry/npc_ob"));  //����job npc
		 me->delete_temp("ry/npc_ob");
	 }
	 
	me->delete_temp("ry");	
	log_file("job/fuxing",sprintf("%8s%-10s �������¸������񣬾��飺%d\n",me->name(),"("+me->query("id")+")",me->query("combat_exp")),me);
	
	return "������͵��ˣ������ʱ���ܾȳ��ν���������";
}


void done(object target, object me,int i)
{
       int count,exp,pot,total_job_times,qing;

       if(me && i >= 0){
		if(target){
			
			message_vision("\n$N��ͷ����"+me->name()+"�������޲���������ָ�㼸�У��͵��ǽ����ɣ�\n", target, me);
		    tell_room( environment(me), target->name() + "��" + me->name()+ "����С����˵��Щ����\n", ({ me, target }) );
		
		qing=(int)me->query_temp("ry/qing");
		if (qing>10) qing=10;
		//�����ȡ���˴��������뽱������ by renlai
			TASKREWARD_D->get_reward(me,"���¸���",-1,0,0,18+qing,0,0,0,"������"); 
     log_file("job/fuxing",sprintf("%8s%-10s��ɵ�%4d�����¸����������񣬾��飺%d\n",me->name(),"("+me->query("id")+")",me->query("job_time/���¸���"),me->query("combat_exp")),me);	
			//me->add("job_time/���¸���", 1);
			me->clear_condition("job_busy");
	        me->clear_condition("riyue_job");
			//me->apply_condition("riyue_job", 3);
			
			if (me->query("family/family_name")=="�������" && !me->query_temp("mz_entrance") && !me->query("quest/xxdf/pass") && me->query("combat_exp")>8000000 )	
		{
			if (QUEST_D->job_questing(me,2,"mz_entrance","���¸���",4000,"ѩɽ",4000,"mz_entrance"))
		     command("say "+me->query("name")+"����˵����÷ׯ��λׯ��ϲ�������黭��������Ͷ��������ȥ����������һ����Ե��\n");	
		}	
			
/*			
			total_job_times=me->query("job_time/���¸���")+me->query("job_time/ѩɽ");
	
	if (wizardp(me)||
	(random(me->query("job_time/���¸���"))>4000 
	   && random(me->query("kar"))>25 
	   && random(me->query("job_time/ѩɽ"))>4000 
	   && me->query("family/family_name")=="�������"
	   && !me->query_temp("mz_entrance")
	   && !me->query("quest/xxdf/pass")
	   && me->query("combat_exp")>8000000
	   && random(10)<5
	   && total_job_times % 50 == 0 ))
	{
		me->set_temp("mz_entrance", 1);
		command("say "+me->query("name")+"����˵����÷ׯ��λׯ��ϲ�������黭��������Ͷ��������ȥ����������һ����Ե��\n");
		log_file("quest/xixing",sprintf("%8s%-10s���¸�������ʱ��ȥ÷ׯ�����£�%4d��ѩɽ��%4d������%2d��\n",
			me->name(),"("+me->query("id")+")",me->query("job_time/���¸���"),me->query("job_time/ѩɽ"), me->query("kar")),me);
			}
			*/
//else  log_file("quest/xixing",sprintf("%8s%-10s���¸�������ʱ��÷ׯ��ʾʧ�ܣ����£�%4d��ѩɽ��%4d������%2d��\n",me->name(),"("+me->query("id")+")",me->query("job_time/���¸���"),me->query("job_time/ѩɽ"), me->query("kar")),me);
			
			me->delete_temp("ry");
	        me->delete_temp("riyue_job");						
			me->set("job_name", "���¸���");
			tell_room(environment(target), target->query("name")+"ҡͷ��Цһ�����ӹ�����������ҩ��һ�����¡�\n", ({target}));
			destruct(target);
			/*
			if(target->return_home()){
				target->delete_temp("riyue_job");
				target->delete_temp("last_lost_to");
				target->clear_condition("riyue_busy");
				target->set("chat_chance", target->query("chat_c"));
				if(!target->query_temp("location"))
				target->delete("location");
				target->set_leader(0);
				target->reincarnate();
			}
			else destruct(target);
			*/
			
		}
	}
	else if(target){
		tell_room(environment(target), target->query("name")+"ҡͷ��Цһ�����ӹ�����������ҩ��һ�����¡�\n", ({target}));
		destruct(target);
	}
}



void attempt_apprentice(object ob)
{
     if(ob->query_skill("tianmo-gong",1) < 350 ||
      ob->query_skill("tianmo-zhang",1) < 350 ||
        ob->query_skill("tianmo-dao",1) < 350){
        command("say ����书��������죬�ٻ�ȥ�����ɡ�");
        return;
        }
     command("say �ã��������б�����Ƚ��������������㻹��������������ˡ�");
     command("recruit " + ob->query("id"));
     ob->set("title","������̹�����ʹ��������");
}


int ask_jiuwen()
{
     object me=this_player();
     if (me->query("family/family_name")!="�������")
         return notify_fail("�㲻������̵�������Ϲ����������\n");

	 if (me->query_skill("tianmo-gong",1)<449)
		 return notify_fail("�����ħ����̫��������450�����Ǻú�����ȥ�ɡ�");
     
	
		
		 command("say �������ν����ᵽ��ʮ����Χ����ɽ֮ս�ۣ���֪Ϊ�ξ�Ȼȫ��ʧ�١�\n");
		 command("think ");
		 command("say ��ʱ�������Ӣ�۱�������Գ��ħ�ų˷硢�ų����ֵܣ�һ����ħ������ɨ���¡�\n");
		 command("say ���д�����ħ���ɳ��ϵĴ�����ħ���������𽭺���\n");
		 command("sigh ");
		 command("say ˭Ҫ���ܰ����ҵ���ľ��Ҿ͸��������ࡣ\n");
		 command("heng ");
		 me->set_temp("hssb/askxiang",1);
		 return 1;
		 //command("");
		//�漴 ѡ����Ҫ���Ȼ�������˾͸�����ȥ��ɽ����
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
	 || room->query("sleep_room")     //add by renlai for no fight sleep room
	 || room->query("quest")          //add by renlai for not enter room
	 || room->query("outdoors") == "���ش��"
	 || room->query("outdoors") == "������"   //add by renlai for not enter zone
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/group/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/xueshan/") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
	 || strsrch(room_name, "/d/baituo/") == 0)
	 return 0;
	return 1;
}

void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/hmy/npc/xiang");
		ob->move("/d/hmy/liangting");
	}
	::die();
}




