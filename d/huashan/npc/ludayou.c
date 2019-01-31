// NPC: /d/huashan/npc/dayou.c
// Date: Look 99/03/25
// Modify By Looklove@SJ 2000/01/07 for add a job
// Lklv Modify at 2001.10.18

#include <ansi.h>
inherit NPC;
string ask_job();
inherit F_MASTER;

void create()
{
        set_name("½����", ({ "lu dayou", "lu", "dayou" }));
        set("nickname", "�����");
        set("long",
"½������ĺ��ݣ��ֳ��ļ�������ģ���������ò�������\n"
"ͬ�������е������ǻ�ɽ������һ���еĺ��֡�\n");
        set("gender", "����");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 13);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);

        set("max_qi", 6000);
        set("max_jing", 3800);
        set("neili", 5000);
        set("max_neili", 5000);
        set("eff_jingli", 3800);

        set("jiali", 150);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("sword", 250);
        set_skill("cuff", 250);
        set_skill("huashan-qigong", 250);
        set_skill("huashan-jianfa", 250);
        set_skill("huashan-shenfa", 250);
        set_skill("poyu-quan", 250);
        set_skill("zhengqi-jue", 250);
		set_skill("strike", 250);
		 set_skill("hunyuan-zhang", 250);

        map_skill("force", "huashan-qigong");
        map_skill("dodge", "huashan-shenfa");
        map_skill("parry", "huashan-jianfa");
        map_skill("sword", "huashan-jianfa");
		map_skill("strike", "hunyuan-zhang");
        map_skill("cuff", "poyu-quan");

        prepare_skill("cuff", "poyu-quan");

        create_family("��ɽ��", 14, "����");

        set("inquiry", ([
              "����" : (: ask_job :),
        ]));

        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}


string ask_job()
{
        object ob, me, dao;
        me = this_player();

        if(me->query("family/family_name") != "��ɽ��")
               return "����һ�ɽ���ӣ���Щ��ǲ��鷳���ˡ�";
        //if ((int)me->query("combat_exp") >= 30000)
        //if ((int)me->query("combat_exp") >= 2000000)
               // return "���书�ѳɣ�����ȥ��ʦ����æ�ɡ�\n";
        if (me->query("shen") < 1000)
                return "����¶�׹�, ����ǲ�������ʲô���£� ";
        if (me->query_temp("hs/kc_job"))
                return "��������ȥ����������ô����ȥ��\n";
        if(me->query_condition("job_busy"))
               return "�����ں�æ����һ�������ɡ�";

        dao = present("chai dao", me);

        if (!dao){
	        ob=new(__DIR__"obj/chaidao");
        	ob->move(me);
        	tell_object(me, "½���и���һ�Ѳ񵶡�\n");
        }
        me->set_temp("hs/kc_job",1);
        me->apply_condition("job_busy", 6+random(6));
        command("ok "+me->query("id"));
        return "�﷿��������˵������������ȱ�����������ȥ�����忳Щ�ɡ�\n";
}

void init()
{
        object me,ob;
        ::init();

        me = this_player();
        ob = this_object();

	    if (
			//interactive(ob) && 
			me->query_temp("jianzong/askyue")) {
		command("say �����ˣ������ˣ�ʦ����ʦ��һ��������������û����ʱ�������кü����˰�ɽ����ɽ����ɽ��̩ɽ�����У����������ڡ�\n ");
		command("say �������������⣬���������˸�����һ��������˵�����ǻ�ɽ�ɵģ���ʱ���˲������ʦ��ȴ��������ʦ�֡�ʦ�ܡ�\n");
		command("say һ���˽�����Ƥ��˵���շ⣬����ô�ⲻƽ������һ���Ǹ����ˣ���һ�����ǰ��ӣ����С�������ô�ģ������ǡ������ֱ����ˡ�\n");
		command("say ���Ƕ�����Ů���أ���Ͻ���ȥ�����ɣ����ƺ�Σ����\n");
		message_vision(HIY"\n\n\n$N����½�������˵������������һ㶣����룬�����ǵ�����˭���ǲ��ǹ�ȥ��������\n"NOR,me);
		me->delete_temp("jianzong/askyue");	
		me->set_temp("jianzong/asklu",1);	
		return ;
	  }
}
void attempt_apprentice(object ob)
{
       
        if (ob->query("shen") < 20000 ) 
		{
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ����,����20k��Ҫ�����ҡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
		return;
        }
        if (ob->query_skill("huashan-qigong",1)<150)
        {
			command("say �һ�ɽ����������������Ļ�ɽ������˲����150���������ң�");
			return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        command("chat* ���ϸ��ֳ�һ˿Ц�ݣ�����"+ob->query("name")+"Ц�����һ�ɽ������Ϊ����֮�ס�");
        command("recruit " + ob->query("id"));
        ob->set("quest/huashan","����");
}
