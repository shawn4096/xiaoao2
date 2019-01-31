// By Spiderii

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_yjj();
int ask_tztg();

void create()
{
        object ob;
        set_name("������ʦ", ({
                "xuansheng dashi",
                "xuansheng",
                "dashi",
        }));
        set("long",
                "����һλ�����ü����ɮ������һϮ��˿�ػ����ġ��������ݸߣ�\n"
                "̫��Ѩ΢΢ͻ�������̵��ϲ�����\n"
        );


        set("nickname", "֤��Ժ����");
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 25000);
        set("max_jing", 7000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 200);
        set("combat_exp", 12500000);
        set("score", 500000);

        set_skill("force", 450);
        set_skill("yijin-jing", 450);
        set_skill("dodge", 450);
        set_skill("shaolin-shenfa", 450);
        set_skill("parry", 450);        
        set_skill("strike", 450);
        set_skill("cuff", 450);
        set_skill("leg", 450);
        set_skill("finger", 450);
        set_skill("staff", 450);
        set_skill("strike", 450);
        set_skill("jingang-quan", 450);
        set_skill("wuchang-zhang", 450);
        set_skill("ruying-suixingtui", 450);    
        set_skill("mohe-zhi", 450);
        set_skill("banruo-zhang", 450);
		 set_skill("hand", 450);
        set_skill("qianye-shou", 450);
        set_skill("buddhism", 160);
        set_skill("literate", 140);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("finger", "mohe-zhi");
        map_skill("strike", "banruo-zhang");
        map_skill("leg", "ruying-suixingtui");
        map_skill("staff", "wuchang-zhang");
        map_skill("parry", "wuchang-zhang");
		map_skill("hand", "qianye-shou");

        prepare_skill("hand", "qianye-shou");
        prepare_skill("leg", "ruying-suixingtui");
         set("chat_chance_combat", 70);
	    set("chat_msg_combat", ({
		(: perform_action, "leg.ruying" :),
		(: perform_action, "hand.qianshou" :),
		(: exert_function, "jingang" :),
	    }));
        create_family("������", 36, "����");

        set("inquiry", ([
                "�׽": (: ask_yjj :),
				"�����ȹ�": (: ask_tztg :),
        ]));


        setup();

        if (clonep()) {
                ob = unew(BINGQI_D("jiuhuan-zhang"));                
                if (!ob) ob = unew(BINGQI_D("chanzhang"));
                ob->move(this_object());
                ob->wield();
                carry_object("/d/shaolin/obj/xuan-cloth")->wear();
        }
       
}


void attempt_apprentice(object ob)
{
        object me; 
        mapping ob_fam, my_fam;
        string name;

        me = this_object();
        my_fam  = me->query("family");

        name = ob->query("name");

        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "������")
        {
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "������") 
        {
                command("say " + RANK_D->query_respect(ob) + "���׼ҵ��ӣ�����������ѧ�ա�");
                return;
        }

        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say " + RANK_D->query_respect(ob) + "��ƶɮ����ҵ� !");
                return;
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "��")
        {
                command("say " + ob_fam["master_name"] + "��ͽ�������ܵ���������ˣ������� !");
                command("recruit " + ob->query("id"));
        }
        else
        {
                command("say " + RANK_D->query_respect(ob) + "���㱲�ݲ��ϣ�����Խ����ʦ��");
                return;
        }

        return;
}
int ask_yjj()
{        
        
        object me = this_player();
        string msg;
        if (me->query_temp("azhu/mask")==1)
        {
			msg = HIY"������ʦ˵��:�׽���Ǳ�������֮��,����������ʮ����������ѧ�ܸ١�\n"NOR;
			 msg+= HIY"������ʦ˵��:��ϧ�������һʱ���ڷ���,��һŮʩ���ٰ�������ɮ�½�֮��ȥ��\n"NOR;
			msg+= HIY"������ʦ˵��:�˺���¹������µ����Ĵ���Ѱ,ȴ����δ�����κ���Ϣ��\n"NOR;
			msg+= HIY"������ʦ˵��:���ŷ���ʦ��Ϊ�����˼��,��ڲ��ѡ�\n"NOR;
			 msg+= HIY"������ʦ˵��:ʩ���д�һ��,Ī��.........???!\n"NOR;
			message_vision(msg, me);
			me->set_temp("azhu/mask2",1);
			return 1;
		}
		message_vision(HIC"������ʦ�ʵ������������Щ��ʲô����\n"NOR, me);
        return 1;


}
int ask_tztg()
{        
        
        object me = this_player();
        string msg;
        if (me->query_skill("shaolin-tantui",1)<450)
		{
			command("say �����ֵ��ȹ�������450�����û�����������\n");
			return 1;
        }
		if (me->query_skill("ruying-suixingtui",1)<450)
		{
			command("say ����Ӱ�����ȹ�������450�����û�����������\n");
			return 1;
        }
		if (me->query("family/family_name")!="������")
		{
			command("say �������������Ե�޹ʣ����˴������������������\n");
			return 1;
        }
		if (me->query_skill("yijin-jing",1)<450)
		{
			command("say �������׽��������450�����û�����������\n");
			return 1;
        }
		if (time()-me->query("quest/sl/rysxt/tiezhou/time")<86400)
		{
			command("say ��˵�ڿ��޳����Ǳ��ݣ���������̫Ƶ���ˣ������߻���ħ��\n");
			return 1;
        }
		command("say ��Ӱ���������Ǳ�����ʮ������֮һ,���������ȷ����۷������\n");
		command("say �������ȹ����ǽ�ȫ����Ѫ�����Ȳ���ʹ���Ȳ������������������һ����\n");
		command("say ���������ϰ�˼��ܣ�����ȥ���߰����ô���ѯ���³����޺�\n");
		me->set_temp("rysxt/askstart",1);
		return 1;


}

int accept_object(object me, object obj)
{
        object letter;
        if ((string)obj->query("id")=="shense baofu") {
        message("vision",me->name()+"��������ʦһ����ɫ������\n",environment(me),
            ({me}));
        letter = unew("/d/mr/npc/obj/letter");
        if (me->query_temp("azhu/mask2") < 1) return notify_fail (CYN"������ʦ˵��������������ʲô?\n"NOR);  

        command("thank "+me->query("id"));
        command("say ��.........!û�뵽��������֮��,���ܵü����澭��");
        command("say ڤڤ�й�Ȼ�����Ӧѭ����ֹ,��λŮʩ�����д�����,�������������,����,����!");
        letter->move(me);        
        message_vision("$n�ݸ�$Nһ�����š�\n", me, this_object() );
        command("say ��λ"+RANK_D->query_respect(me)+",�鷳����ƶɮ��ת��λŮʩ��������������һ��,�����ˡ�");
        me->set_temp("azhu/mask3",1);

        remove_call_out("destroying");
        call_out("destroying", 1, this_object(), obj);
        return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}




