// qiu.c �𴦻�
// Modified By action@SJ 2008/8/12
// Update By action@SJ 2009/2/21

#include <ansi.h>
#include <get_place.h>

inherit NPC;
//inherit F_MASTER;
mixed qixing();
mixed qzjf_jianjue();
int do_qingjiao();
string ask_duan();
string ask_fengxue();
int ask_chujian();
int ask_fangqi();
object get_where();

string ask_tonggui();

#define QUESTDIR "quest/���Ӣ�۴�/"
#define QUESTDIR1 "quest/���Ӣ�۴�/��ѩ����/"
#define QUESTDIR2 "quest/���Ӣ�۴�/�����߹�/"

void create()
{
		set_name("�𴦻�", ({"qiu chuji", "qiu"}));
		set("long",
					"�����ǽ������˳ơ������ӡ����𴦻������ˣ�����������\n"
					"�����⣬��ĿԲ����˫ü�絶����ò���ϣ�ƽ���������\n");
		set("title","ȫ������֮��");
		set("gender", "����");
		set("age", 26);
		set("nickname",HIM"������"NOR);
		set("shen_type",1);
		set("attitude", "peaceful");

		set("str", 50);
		set("int", 55);
		set("con", 50);
		set("dex", 50);

	    set("max_qi", 48000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 200);

		set("jingli", 7000);
		
set("eff_jingli", 7000);

		set("combat_exp", 12000000);

        set_skill("force", 480);
        set_skill("xiantian-gong", 480);
        set_skill("sword", 480);
        set_skill("quanzhen-jianfa",480);
        set_skill("dodge", 480);
        set_skill("jinyan-gong", 480);
        set_skill("parry", 480);
        set_skill("strike", 480);
        set_skill("haotian-zhang", 480);
        set_skill("literate", 250);
		set_skill("tiangang-beidouzhen",480);
 
        set_skill("leg", 480);
        set_skill("yuanyang-lianhuantui", 480);

		set_skill("taoism",200);
	    set_skill("medicine", 200);
        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("strike", "haotian-zhang");
		map_skill("parry", "quanzhen-jianfa");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg","yuanyang-lianhuantui");
		prepare_skill("strike","haotian-zhang");

	    create_family("ȫ���", 2, "����");

	    set("inquiry", ([               
                "ȫ�潣��" : (: qzjf_jianjue :),
			    "��ѩ����" : (: ask_fengxue :),
				"����" : (: ask_duan :),
			   "���Ǿ�����" : (: qixing :),
			   "ȫ�����" : (: ask_chujian :),
			   "����" : (: ask_fangqi :),
				"ͬ�齣��" : (: ask_tonggui :),
           ]));		       
                    

        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                 (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
					(: exert_function, "wuqi" :),
					(: exert_function, "yusuo" :),
               
        }));
        	setup();
	carry_object("/d/wudang/obj/greenrobe")->wear();
	carry_object("/clone/weapon/sword")->wield();
	//add_money("silver",50);
}


void init()
{
	object me, ob;
	::init();
	ob = this_player();
	me = this_object();

	add_action("do_qingjiao", "qingjiao");

}

string ask_fengxue()
{	
	object me;
	me=this_player();
	if (!me->query(QUESTDIR1+"over"))
	{
		return "���Ӣ�۴���һ�½���δ��ɣ��޷������ڶ��½�\n";
	}
	
	if (me->query(QUESTDIR2+"over"))
	{
		return "���Ѿ��ͽ����߹�Լ������һ���������������ˣ��㻹������ȥ�ҹ�����˺��ˡ�\n";
	}
	
	if ((time()-me->query("quest/���Ӣ�۴�/time"))<86400)
	{
		return "������Ѿ������ˣ���ȥ��Ϣһ�°ɣ�\n";
	}
	
	
	
	message_vision(HIR"$N����ǰţ�Ҵ巢��һЩ����ԭԭ����˵�����𴦻������𴦻���Ϊ�𾪣�\n"NOR,me);
	command("angry ");
	command("say ��Ȼ�������£�\n");
	command("say ��ô���͵ܺ͹��͵�һ��������Ϊƶ�����ܵ�ǣ��ô��\n");
	command("say ���У��ұ���Ҫȥ�ҵ����͵ܵķ��˺����͵ܵķ��˰�ϧ�������������Ѱ���\n");
	command("say ��֪���������˭�ɵ�ô����Ҳ���и�׷���������\n");
	me->set_temp(QUESTDIR2+"start",1);
	me->set(QUESTDIR2+"start",1);
	return "�䵶ɽ�𺣱ز���Ҳ��\n";

}
string ask_duan()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR2+"start"))
	{
		return "�����������ٺ�һ����\n";
	}
	message_vision(HIY"$N�����𴦻�����ʱ�����ǵ��عٱ���Ϊ������Ϊ������Χ��ţ�Ҵ壬��ʵ���˲��⣡\n���������ġ���ϧ�������䲻��������ƼȴΪ��������°�ߣ���˵���˿����ں��ݱ�Ӫһ�����֣�\n"NOR,me);
	command("consider ");
	command("say ��Ȼ���ֵܺͰ�ϧ��û����ʬ�壬��˵������û�б�����\n");
	command("say ������ȥ��Ԯ���Ƕ��ˣ�������ⶾ��,��ȥѰ�����͵ܺ�����ˣ�\n");
	command("say ����ȥ���ݱ�Ӫһ����̽�鿴���������Ǻ�ԭ��������ԩ������\n");
	me->delete_temp(QUESTDIR2+"start");
	me->set_temp(QUESTDIR2+"hzdatan",1);
	return "��͢���پ�Ȼ���ɱ�ˣ�����û�������ˣ���\n";

}

void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="����")
       {
		   command("say ��һ��Ů�˼�������Ϊʦ���ѵ�����ʲô��ͼ���ɣ���\n");
		   command("say ��ȫ��һ��������ȫ���ڵ���Ϊ�ϣ����������������Ҳ��ó���\n");
		   command("say �㻹��ȥѰ����ʦ���徲ɢ���ﲻ���������Ƿ����㣿\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 2000000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(2m)");
               return;
       }
	   if (ob->query("party/gongji") < 3000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(��Ҫ3000�����ɹ���ֵ)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say ��������еմ����ӣ�����������");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 350) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����350��������������");
               return;
       }
	 
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("title", "ȫ�������״�����");
       ob->set("class","taoism");
	   return;
}

mixed qzjf_jianjue()
{
	object me = this_player();
	object ob = this_object();
	int exp, time, night;
	mixed *local;
	night = 0;
	local = localtime(time() * 60);
	if (local[2] < 5 || local[2] >= 19) night = 1;

	if( me->query("family/family_name") != "ȫ���" )
		return RANK_D->query_respect(me) + "�뱾��������������֪�˻��Ӻ�̸��";
    if (!me->query("quest/qz/dichuan"))
	{
		return "����Ҵ�ȫ��մ����ӣ���ΪʲôҪ�����㣿";
	}
    if (!night) 
	  return "�������޷���������б������ǣ������ָ����ѧϰȫ�潣���Ľ������衣\n";
  
    if (!me->query(QUESTDIR2+"over"))
	{
		return "����δ�������Ӣ�۴��ڶ��½����̣�����Ҳ�״\n";
	}
	if (me->query_skill("quanzhen-jianfa",1)<450)
	{
		return "ȫ�潣����Ҫ�ﵽ450��ɽ׶η�����ϰ��\n";
	}
	if (me->query_skill("force",1)<450)
	{
		return "ȫ�潣����Ҫ�����ڹ��ﵽ450��ɽ׶η�����ϰ��\n";
	}
	if (me->query("family/family_name")!="ȫ���")
	{
		return "�㲢��ȫ��̵��ӣ�\n";
	}
	if ((time()-me->query("quest/qz/qzjf/jianqi/time"))<86400)
	{
		return "������̫Ƶ���ˣ�\n";
	}
	if (me->query("quest/qz/qzjf/jianqi/pass"))
	{
		return "���Ѿ��⿪��������ˣ�\n";
	}
  
  

	if( me->query("quest/qzjf/jianjue") )
		return RANK_D->query_respect(me) + "����Ľ��������Ѿ����ڱ���֮���ˣ��ֺιʿ�����Ц�أ�";

    if( me->query_skill("quanzhen-jianfa", 1) < 300 )
		return RANK_D->query_respect(me) + "����Ľ������費�������޷��������ɽ����ľ�Ҫ���ڣ�";

	time = time() - me->query("qzjf/jianjue/time");
	if( me->query("qzjf/jianjue/time") && time < 86400 && !wizardp(me) )
		return "�ţ��㲻�Ǹ�����̹��ҽ����𣿻�����Ŭ����ʱ��ɣ�";

	if( me->query_temp("marks/qzjf/qingjiao") )
		return RANK_D->query_respect(me) + "���ҸղŲ����Ѿ��ش�������";

	message_vision(CYN"$N����Ŀ���$n������˵���������ɵ�ȫ�潣���������ǵ��ҹ۲������Ƕ��������Ǳ任֮����ȡǧ���򻯡������޾�֮ԭ��\n"
	"�粻�����������ƺ������򣬽�������书������С�ɣ�����������ģ��������������һ�¡�("HIY"qingjiao"CYN")��\n"NOR, ob, me);

	me->set_temp("marks/qzjf/qingjiao", 1);
	return 1;
}

int do_qingjiao()
{
	object me, ob, weapon, weapon1;
	int i,j;
	me = this_player();
	ob = this_object();

	weapon1 = ob->query_temp("weapon");

	if( !me->query_temp("marks/qzjf/qingjiao") ) return notify_fail("ʲô��\n");

	if( me->is_busy() || me->is_fighting() ) return notify_fail("����æ���ء�\n");

	if( ob->is_busy() || ob->is_fighting() ) return notify_fail(ob->name()+"��æ���ء�\n");

	if( me->query("qi") < me->query("max_qi")*9/10 )
		return notify_fail("������״̬���ѣ����ǵȻ�����̰ɣ�\n");

	if( me->query("eff_qi") < me->query("max_qi")/2 )
		return notify_fail("�����������������ǵȻ�����̰ɣ�\n");
	if ((time()-me->query("quest/qz/qzjf/jianqi/time"))<86400)
	{
		command("say ������̫Ƶ���ˣ��޵���ɻ��ĸ����꣡�㵱��Ϣһ��������\n");
		return 1;
	}
	if( !weapon = present("qixing jian", me) ) 
	{
		message_vision(CYN"$N��$n˵������ʦ����ͽ������ָ��"+RANK_D->query_self(me)+"��ȫ�潣����������\n"NOR, me, ob);
		message_vision(CYN"$n˵����" + RANK_D->query_respect(me) + "������ȥ����ʦ��������ȡ�����Ǳ����ɣ���\n"NOR, me, ob);
		me->start_busy(1);
		return 1;
	} else {
		me->start_busy(1);
		message_vision(CYN"$N����$n����������ʦ��˵��������ʦ��ָ��"+RANK_D->query_self(me)+"��ȫ�潣����������\n"NOR, me, ob);
		me->delete_temp("marks/qzjf/qingjiao");
		me->set("qzjf/jianjue/time", time());
		me->set("qzjf/jianjue/exp", me->query("combat_exp"));

		if( weapon1 ) weapon1->unequip(ob); 
		weapon->move(ob);
		weapon->wield(ob);
		ob->set("jiali", 0);
		ob->set("neili", query("max_neili")*2 );
		ob->set("jingli", query("eff_jingli")*2 );
		message_vision(HIW"$nĬ��ȫ�潣������"HBRED+HIW"�����ȴӱ��������ɱ�������չ������"NOR+HIW"����ʱ�����ݺᣬ��$N�������ֲ�����"NOR, me, ob);
		ob->set_temp("qzjf/jianjue", 1);
		COMBAT_D->do_attack(ob, me, weapon, 1);
		if( me->query("qi") >= me->query("max_qi")*1/10 ) COMBAT_D->do_attack(ob, me, weapon, 1);
		if( me->query("qi") >= me->query("max_qi")*1/10 ) COMBAT_D->do_attack(ob, me, weapon, 1);
		if( me->query("qi") >= me->query("max_qi")*1/10 ) {
			message_vision(HIW"$nĬ��ȫ�潣������"HBMAG+HIW"������ָ�����½Դ���������ָ�����½��ġ�"NOR+HIW"�������͵��˽���ת����������ָ��֮��һ��ָ���澢����"NOR, me, ob); 
			weapon->unequip(ob); 
			COMBAT_D->do_attack(ob, me, 0, 1);
			weapon->wield(ob);
		}
		if( me->query("qi") >= me->query("max_qi")*1/10 ) COMBAT_D->do_attack(ob, me, weapon, 1);
		if( me->query("qi") >= me->query("max_qi")*1/10 ) {
			message_vision(HIW"$nĬ��ȫ�潣������"HBBLU+HIW"������ָ�����½��������ָ�����½Զ���"NOR+HIW"��������"+weapon->name()+HIW"�͵Ļ�ת�ٴδ̳���"NOR, me, ob);
			COMBAT_D->do_attack(ob, me, weapon, 1);
		}
		ob->delete_temp("qzjf/jianjue");

		if( me->query("qi") < me->query("max_qi")*1/20 ) {
			message_vision(CYN"$n�ǳ�ʧ���Ķ�$N˵������"+me->name()+"�����书δ�ɣ����ǵ����û�����˵����\n"NOR, me, ob);
			weapon->unequip(ob); 
			destruct(weapon);
			if( weapon1 ) weapon1->wield(ob);
			me->start_busy(1);
			me->set_temp("marks/ʧ��", 1);
			return 1;
		}
		weapon->unequip(ob); 
		weapon->move(me);
		message_vision(CYN"\n$n�����Ǳ���������$N������˵�ţ���"+me->name()+"�����Լ�������ĥ������ʹ�õĽ����ɣ���\n"NOR, me, ob);
		if( weapon1 ) weapon1->wield(ob);
		message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	//�����жϺ���
		call_out("ask_jianqi",1+random(3));
		message_vision(HIY"�𴦻���$N˵������ܲ�����ȫ�潣�������Ҵ�ȫ��ĺ����似�������ܷ������ˣ���\n"NOR,me);

		/*if( random(me->query("kar")) > 25) 
		{	// �����Դ
			message_vision(HIW"$NͻȻ��׽ס����˲���һĻ�����������ǰ�����ң�ȫ�޶��򣬺����ˣ��ȷ������ˡ������������ȫ�潣�������С�\n", me);
			tell_object(me, BYEL"��ϲ�㣬����" + NATURE_D->game_time() + "������ȫ�潣����\n"NOR);
			me->set("quest/qz/qzjf/jianqi/pass", 1);
		} else {
			message_vision(HIC"$Nҡ��ҡͷ�������������Ǻ����ѵġ���˵�գ������̾�˿�����\n", me);
			me->set_temp("marks/ʧ��", 1);
		}*/
	}
	return 1;
}
string ask_jianqi()
{
	object me;
	int i,j;
	me=this_player();
	
	me->set_temp("quest/qz/qzjf/jianqi/askqiu",1);
	
	command("say ���������������������Ҫ�۳�������ɹ���ֵÿ��100�㣬���������û�ʸ�����ҡ�\n\n\n\n");
	
    command("say �ðɣ���Ȼ�����Ŭ�����Ҿ͸��������о��ϡ�\n");
    command("whisper "+me->query("id"));
	  
	if (me->is_busy())
	{
	  return "������æµ��!\n";
	}
	me->start_busy(10);
	if (me->query("party/gongji")<100)
	{
		return "������ɹ�������\n";
	}
	
	me->add("party/gongji",-100);
	
		command("say ��������ô��\n");
		command("pat "+me->query("id"));
		
		if (QUEST_D->questing(me,3,80,0,"qz/qzjf/jianqi"))		
		{
			tell_object(me,HIC"\n�����˵��𴦻�������ָ�㣬�����������Լ�����ȫ�潣���������ĵã�����ӡ�ա�\n"NOR);
			message_vision(HIW"$NͻȻ��׽ס����˲���һĻ�����������ǰ�����ң�ȫ�޶��򣬺����ˣ��ȷ������ˡ������������ȫ�潣�������С�\n", me);
			tell_object(me, BYEL"��ϲ�㣬����" + NATURE_D->game_time() + "������ȫ�潣����\n"NOR);
			//me->set("quest/qz/qzjf/jianqi/pass", 1);
			//log_file("quest/qzjfjianqi", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��ȫ�潣����������,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			//	me->name(1),me->query("id"), me->query("quest/qz/qzjf/jianqi/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "��ϲ����ȫ�潣�����������ɹ�!\n";
			
		}	
	   else
		{
			//log_file("quest/qztonggui", sprintf("%8s(%8s) ����ȫ�潣������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			//	me->name(1),me->query("id"), me->query("quest/qz/qzjf/jianqi/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"�������𴦻���ָ�㣬���Ƕ�ȫ�潣�������İ���ȫȻ����Ҫ�졣\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			//me->add("quest/qz/qzjf/jianqi/fail",1);
			//me->set("quest/qz/qzjf/jianqi/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			//me->start_busy(2);
			return "�ǳ��ź�����ȫ�潣������ʧ��"+me->query("quest/qz/qzjf/jianqi/fail")+"�Ρ�\n";
		}

}

mixed qixing()
{
	object room;
	object me = this_player();
	object ob = this_object();
	int exp, time, night;
	object* ppl;
    int i,j = 0;

	mixed *local;
	night = 0;
	local = localtime(time() * 60);
	if (local[2] < 5 || local[2] >= 19) night = 1;
    time = time() - me->query("quest/quanzhen/lianzhen/time");
	//�ж��Ƿ������ڽ���
	ppl = users();
	i = sizeof(ppl);
    while(i--)
	{
       if( userp(ppl[i])&& !wizardp(ppl[i])&& ppl[i]->query_temp("quest/qixing/enter"))
	   j++;
    }
	if (j>0)
	{
		command("say �ȵȣ�\n");
		return "�����������ڲ����Ժ�\n";
	}

	if (!me->query("quest/qz/dichuan"))
	{
		command("say ������\n");
		return "����Ҵ�ȫ��մ����ӣ���ΪʲôҪ�����㣿\n";
	}
	if (me->query("int")<40)
	{
		command("say ������\n");
		return "����������Բ���40��������Ҳ�����ˣ�\n";
	}

	if( time < 86400 && !wizardp(me) )
		return "�ţ��㲻�Ǹ�����̹������Ǿ������𣿻�����Ŭ����ʱ��ɣ�\n";
	
	if( me->query("family/family_name") != "ȫ���" )
		return RANK_D->query_respect(me) + "�뱾��������������֪�˻��Ӻ�̸��\n";
    if( me->query("family/family_name") != "ȫ���" )
		return RANK_D->query_respect(me) + "�뱾��������������֪�˻��Ӻ�̸��\n";
	if( me->query_skill("xiantian-gong",1)<450 )
		return RANK_D->query_respect(me) + "������칦����450��ץ��Ŭ����\n";
    if (!night) 
		return "�������޷���������б������ǣ������ָ����ѧϰ���Ǿ����������衣\n";
 
	if( !me->query("quest/qz/qzjf/qixing/start") )
		return RANK_D->query_respect(me) + ",������͵����������ȥ���飬�������᣿\n";	
	
	if( me->query("quest/qz/qzjf/qixing/pass") )
		return RANK_D->query_respect(me) + ",���Ѿ����������Ǿ������İ��أ��ֺιʿ�����Ц�أ�\n";

    if( me->query_skill("quanzhen-jianfa", 1) < 450 )
		return RANK_D->query_respect(me) + "����Ľ������費�������޷��������ɽ����ľ�Ҫ���ڣ�\n";

	me->start_busy(5);

	
    me->set_temp("quest/qixing/asked",1);
	message_vision(HIY"$Ņͷ���˿���գ�����������ҫ����̾һ��,����ĬȻ���Ȼ���쳣����Ŀ���$n��\n"+
		HIC"������˵��������ʦ�书���������������һΪ���칦������������Ǿ��������Դ�����������������£�\n"+
		HIG"��ϧ����������������ֵܶ�û����ȫ��������������һ���Ȼ��Ц�����������칦�˾����似��\n"+
		"�������Ǿ�����ȴ�Ǽ�ʦҹ�۱��������򣬽����������汱�����Ǳ任֮����ȡǧ���򻯡������޾�֮ԭ��\n"+
	   HIR"�粻�����������ƺ������򣬽�������书������С�ɣ�����������Ĳ���͸�����Ϳ�����컯�ˡ�\n"NOR, ob, me);
   
    me->move("/d/quanzhen/midong");
	return 1;
}






//ȫ����� job


int ask_chujian()
{
	object me,jianxi,ling;
	mixed objwhere;
	string str;
	me=this_player();
	
	if (me->query("family/family_name")!="ȫ���")
	{
		command("say "+me->query("name")+",�㲻���ҽ��е��ӣ�����������\n");
		return 1;
	}
	if (me->query_skill("xiantian-gong",1)<350)
	{
		command("say "+me->query("name")+",��������е�Σ�գ�������칦����350������������\n\n");
		return 1;
	}
	if(me->query("job_name") == "ȫ�����") 
	{
        command("say "+me->query("name")+",��ս���ȫ����飬��������Ϣһ��ɡ�");
	    return 1;

	}
	if(me->query("shen") <0) 
	{
        command("say "+me->query("name")+",����аħ���֮����������ȫ�����Ұ���ѵ��������Լ���̫Ӳ��ô��");
	    return 1;
	}
	
	if (me->query_temp("qzjob/jianxi"))
	{
		command("say "+me->query("name")+",����һ������û����ء�\n");
	    return 1;
	}
	if (me->query_condition("job_busy"))
	{
		command("say "+me->query("name")+",����������æ�У���������Ϣһ��ɡ�\n");
	    return 1;
	}
	
	if (me->query_condition("qzjob_jianxi"))
	{
		command("say "+me->query("name")+",������ִ��׷ɱ�����ϸ������,Ϊɶ���Ͽ�ȥ��\n");
	    return 1;
	}

	command("say "+me->query("name")+",��������ֽ�������ɳ�������ϸ��͸����ԭ��\n");
	command("say ���պ�����Ǳ�뵽�Ҵ��ξ��ڣ�ͼı���졣\n");
		
    if (me->query("combat_exp")<300000) 
	{
		command("say ��ľ��鲻��3m���Ͻ�����ȥ��\n");
		return 1;
	}                 
				 
	objwhere=get_where();

	if(objwhere) str= get_place(base_name(objwhere))+objwhere->query("short");
	if (present("chongyang ling",me)) 
	{
		command("say �����ϲ��ǻ���������ô��\n");
		return 1;
	}
	jianxi=new("/d/quanzhen/npc/jinbing");
	
	message_vision(HIY"$n��$N˵������"+me->query("name")+HIY"���������ǽ�����պ��ҵ�����������װ������Ҵ��Σ���\n"NOR,me,this_object());
	message_vision(CYN"$n��$N˵�����������зɸ봫���֪�������ϸӦ����"HIY+str+CYN"һ���������ȥ������ȥ��\n��"NOR,me,this_object());
	message_vision(CYN"$n��$N˵�������Ҹ���һö�������������������ƣ��Ա��������֧Ԯ���мǣ�ɱ�������󽻻������\n"NOR,me,this_object());
	
	ling=new("/d/quanzhen/npc/obj/chongyangling");

	ling->set("owner",me->query("id"));
	
	ling->move(me);
	//���ֳ���spuer npc
	
	if (!random(3))
	{
		message_vision(CYN"$n��$N˵�������ݿɿ���Ϣ���������ڻ��������ڸ��֣���ҪС�ģ���\n"NOR,me,this_object());
		me->set_temp("qzjob/super",1);
		ling->set_temp("qzjx/super",1);
		jianxi->set_temp("qzjx/super",1);
		jianxi->set_temp("type_speical");
	}
	
	jianxi->set_temp("target",me->query("id"));
    //�趨npc���20���Ӳ�ɱ�Զ���ʧ
	jianxi->apply_condition("npcdie_job",80);
	jianxi->move(objwhere);

	me->set_temp("qzjob/jianxi", 1);
	me->apply_condition("job_busy",20);
	me->apply_condition("qzjob_jianxi",20);
	return 1; 

}  
int ask_fangqi()
{
	
	object me=this_player();
	if (me->query_temp("qzjob"))	{
		
	    message_vision(HIC"�𴦻���"+me->query("name")+"��̾һ����������Ȼ�겻��Ҳû��ϵ���´������ɡ���\n"NOR,me);
		me->delete_temp("qzjob");
		me->apply_condition("job_busy",6+random(5));
		return 1;
	}
	command("say "+me->query("name")+",�㵽��Ϲ�ܣ�ʲô��û�ɳɣ�Ҫ����ɶ�ء�\n");
	return 1;

}
//������Ʒ
int accept_object(object who, object ob)
{
	
	int gold,getshen,jobs;
	
	jobs=who->query("job_time/ȫ�����");
	
	//ȫ�����ӿ�,��������

	if (ob->query_temp("killer")==who->query("id")
		&& ob->query("owner")==who->query("id")
		&& who->query_temp("qzjob/jianxi")		
		&& ob->query("id")=="chongyang ling")
	{
		getshen=1;
		gold=1+random(1);				
		
		who->set("job_name","ȫ�����");			
		who->apply_condition("job_busy",3);		
		who->delete_temp("qzjob/jianxi");		
		tell_object(who,RED"\n�𴦻����ֽ�"+ob->query("name")+RED+"���뻳�У�С�ķźã�\n"NOR);
		command("say �ܺã�"+who->query("name")+"����Ȼ��������ϸ��ɱ�ˣ�Ϊ��Ϊ����֮���ߣ�\n");
		tell_object(who,GRN"\n�𴦻��ó����ɼ�¼��������"+who->query("name")+HIY+chinese_number(gold)+GRN"������ɹ����Ľ�����\n"NOR);
		who->add("party/gongji",gold);

		//Ԥ��������ʾ�ӿ�
		//���Ǿ�����
		//����40���ϣ�50��������
		if (random(who->query("job_time/ȫ�����"))>4000
			&& random(who->query("kar"))>28
			&& who->query("int")>40
			&& !who->query("quest/qz/qzjf/qixing/start")
			&& jobs % 50 ==0	
			&& who->query("quest/qz/dichuan"))
		{
			
				message_vision(HIC"�𴦻���Զ����$N�����˴�Ĵָ��˵���������������Ϊ�Ҵ�ȫ�������ϸ�����ǲ�����\n"NOR,who);
				command("say "+who->query("name")+"���Ҿͽ�ȫ�潣���й������Ǿ���������Ϣ͸©���㣡\n");
				command("chat* thumb "+who->query("id"));
				command("rumor "+who->query("name")+"����𴦻���������ý������Ǿ������Ļ��ᣡ\n");
				command("chat "+who->query("name")+"����ȫ�����ӵĺ��ĵ��ӣ�������ͬ������չˣ�\n");
				who->set("quest/qz/qzjf/qixing/start",1);
		}
		if (ob->query("super"))
		{
			command("say "+who->query("name")+"���㾹Ȼ�����ϸͷ�Ӷ���ɱ�ˣ��ҾͶཱ�������ɹ�����\n");
			tell_object(who,GRN"\n�𴦻��ָ���"+who->query("name")+HIY+chinese_number(gold)+GRN"��Ķ������ɹ����Ľ�����\n"NOR);

			who->add("party/gongji",gold);
			TASKREWARD_D->get_reward(who,"ȫ�����",getshen,0,0,6+random(4),0,0,0,this_object());
		}else
			TASKREWARD_D->get_reward(who,"ȫ�����",getshen,0,0,3+random(4),0,0,0,this_object());
		who->set("job_name", "ȫ�����");
		who->delete_temp("qzjob");
		who->clear_condition("qzjob_jianxi");
		who->apply_condition("job_busy",3);
		who->apply_condition("qzjx_job_busy",4);
		destruct(ob);
		return 1;
	}

}
void die()
{
	object ob;
	ob=this_object();
	
	if (!query_temp("living"))
	{		
		ob = new("/kungfu/class/quanzhen/qiuchuji");
		ob->move("/d/quanzhen/laojundian");
	}
	::die();
}

//����϶npcλ��
int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
		|| !ob->query("startroom")      // add by Yuj@SJ to void job NPC
		|| ob->query("env/invisibility")
		|| ob->query("no_quest")
		//|| member_array(ob->query("id"), no_kill_list) != -1
		|| userp(ob)
		|| ob->query("attitude")=="aggressive"
		|| ob->query("have_master")
		|| !objectp(room=environment(ob))
		|| room->query("no_fight")
		|| room->query("quest")
		|| room->query("outdoors") == "���ش��"
		|| room->query("short") == "���º�ȭ��"
		|| room->query("short") == "��ɮ��"
		|| strsrch(room_name = file_name(room),"/d/") != 0                    //modified by campsun 2004.2.4 Ϊ�˺�bx code����
		|| strsrch(room_name, "/d/wizard/") == 0
		|| strsrch(room_name, "/d/wuguan/") == 0
		|| strsrch(room_name, "/d/death/") == 0
		|| strsrch(room_name, "/d/mingjiao/lsd/") == 0
		|| strsrch(room_name, "/d/mingjiao/bhd/") == 0
		|| strsrch(room_name, "/d/shaolin/fumoquan") == 0
		|| strsrch(room_name, "/d/xiakedao/") == 0
		|| strsrch(room_name, "/d/luoyang/") == 0    
		|| strsrch(room_name, "/d/beijing/") == 0
		|| strsrch(room_name, "/d/baituo/") == 0)
		return 0;
	return 1;
}

//���λ�ú���

object get_where()
{
	object* living;
	object target;
	int i,j;
	string str;
	
	living = livings();
	
	for (i=0;i < sizeof(living);i++)
	{
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		
		if(check(living[j]) )
		{
			target = living[j];
			str = environment(target)->query("short");
			if( str == "��ɮ��"
			 || str == HIR"������"NOR
			 || str == "��շ�ħȦ" ) continue;
			if( get_place(base_name(environment(target)))!="" )
				break;
		}
	}
	
	if(target && environment(target) ) return environment(target);
	
	return 0;
}
//ͬ�齣��
string ask_tonggui()
{
	object me;
	int i,j;
	me=this_player();
	if (!me->query(QUESTDIR2+"over"))
	{
		return "����δ�������Ӣ�۴��ڶ��½����̣�����Ҳ�״\n";
	}
	if (me->query_skill("tonggui-jian",1)<450)
	{
		return "ͬ�齣����Ҫ�ﵽ450��ɽ׶η�����ϰ��\n";
	}
	if (me->query_skill("force",1)<450)
	{
		return "ͬ�齣����Ҫ�����ڹ��ﵽ450��ɽ׶η�����ϰ��\n";
	}
	if (me->query("family/family_name")!="ȫ���")
	{
		return "�㲢��ȫ��̵��ӣ�\n";
	}
	if (time()-me->query("quest/qz/tgj/tonggui/time")<86400)
	{
		return "������̫Ƶ���ˣ�\n";
	}
	if (me->query("quest/qz/tgj/tonggui/pass"))
	{
		return "���Ѿ��⿪��������ˣ�\n";
	}
	command("consider ");
	message_vision(HIY"�𴦻���$N˵������ܲ�����ͬ�齣��������ȫ������һ������似��\n"NOR,me);

	command("say �������������칦��ԭ����ͬ�齣Ҳ�ǲ���ѧ�ġ�\n");
	command("say ��ȫ���������������Ҳ�ǲ�������������ˡ�\n");
	command("say ���������ܲ���������һ��һ���ֿ�Ϊ�������ˣ��Ǿ�̫��ֵ�ˡ�\n");
	command("say Ϊ�˶Ը����������������Դ���������ͬ�齣����\n");
	command("say ������һ��ʩչ������ȫ��ǿ����Ϊ������������һ��������\n");
	command("say �������Ž�����Υ��ȫ��̵�����ʤǿ���������İ��⣬��Ҳ������֮�٣�\n");
	command("say ���Ȼ�����Ź������Ȥ�Ҿʹ����㣬����Ҫע�����Ź������������ȫ��ǿ�����׶�������֮��֮��\n");
	me->set_temp("quest/qz/tgj/tonggui/askqiu",1);
	
	command("say ���������������������Ҫ�۳�������ɹ���ֵÿ��100�㣬���������û�ʸ�����ҡ�\n\n\n\n");
	
    command("say �ðɣ���Ȼ�����Ŭ�����Ҿ͸��������о��ϡ�\n");
    command("whisper "+me->query("id"));
	  
	if (me->is_busy())
	{
	  return "������æµ��!\n";
	}
	me->start_busy(10);
	if (me->query("party/gongji")<100)
	{
		return "������ɹ�������\n";
	}
	
	me->add("party/gongji",-100);
	i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		command("say ��������ô��\n");
		command("pat "+me->query("id"));
		if( i<4
			&& me->query("kar")<31
			&& j >= 24 ) 
		{
			tell_object(me,HIC"\n�����˵��𴦻�������ָ�㣬�����������Լ�����ͬ�齣���������ĵã�����ӡ�ա�\n"NOR);
			tell_object(me,HIR"\n��Ȼ�͹�Ѩһ�ɴ������������ʱ�о�����������˲����������ͬ�齣�������������š�\n"
						NOR);
			me->set("quest/qz/tgj/tonggui/pass",1);
			log_file("quest/qztonggui", sprintf("%8s(%8s) ʧ��%d�κ�ѧ��ͬ�����,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/qz/tgj/tonggui/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "��ϲ����ͬ������ɹ�!\n";
			
		}	
	   else
		{
			log_file("quest/qztonggui", sprintf("%8s(%8s) ����ͬ�����ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/qz/tgj/tonggui/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"�������𴦻���ָ�㣬���Ƕ�ͬ������İ���ȫȻ����Ҫ�졣\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/qz/tgj/tonggui/fail",1);
			me->set("quest/qz/tgj/tonggui/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			me->start_busy(2);
			return "�ǳ��ź�����ͬ�����ʧ��"+me->query("quest/qz/tgj/tonggui/fail")+"�Ρ�\n";
		}

	


}