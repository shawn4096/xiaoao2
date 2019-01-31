// Npc: /kungfu/class/shaolin/xuan-ku.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me();
int ask_ranmu();
int ask_shoudao();

void create()
{
        object ob;
        set_name("�����ʦ", ({
                "xuanku dashi",
                "xuanku",
                "dashi",
        }));
        set("long",
                "����һλ�����ü����ɮ����һϮ��˿�ػ����ġ�������ݸߣ�\n"
                "�����������ƣ��ֱ۴������¶���ƺ��þ���˪��\n"
        );


        set("nickname", "�޺�������");
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");
        
        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 38000);
        set("max_jing", 8000);
        set("neili", 35000);
        set("max_neili", 35000);
        set("jiali", 200);
        set("combat_exp", 12000000);
        set("score", 500000);

        set_skill("force", 500);
        set_skill("yijin-jing", 500);
		set_skill("ranmu-daofa", 500);

        set_skill("dodge", 500);
        set_skill("shaolin-shenfa", 500);
        set_skill("parry", 500);
        set_skill("cuff", 500);
        set_skill("club", 500);
        set_skill("blade", 500);
        set_skill("sword", 500);
        set_skill("luohan-quan", 500);
		set_skill("ruying-suixingtui", 500);
		set_skill("leg", 500);
		set_skill("hand", 500);
		set_skill("qianye-shou", 500);
        set_skill("weituo-chu", 500);
        set_skill("xiuluo-dao", 500);
        set_skill("fumo-jian", 500);
        set_skill("buddhism", 200);
        set_skill("literate", 150);
        set_skill("zui-gun",500);
        map_skill("force", "yijin-jing");
		map_skill("dodge", "shaolin-shenfa");
		map_skill("parry", "luohan-quan");
        map_skill("cuff", "luohan-quan");
        map_skill("club", "weituo-chu");
        map_skill("blade", "ranmu-daofa");
        map_skill("sword", "fumo-jian");
		 map_skill("leg", "ruying-suixingtui");
        map_skill("hand", "qianye-shou");


        prepare_skill("hand", "qianye-shou");
        prepare_skill("leg", "ruying-suixingtui");
        create_family("������", 36, "����");
        set("chat_chance_combat", 70);
	    set("chat_msg_combat", ({
			(: perform_action, "leg.ruying" :),
			(: perform_action, "hand.qianshou" :),
			(: exert_function, "jingang" :),
	    }));
        set("inquiry", ([
                "ʮ���޺���"       : (: ask_me :),
			    "ȼľ�ֵ�����"       : (: ask_shoudao :),
			    "ȼľ����"       : (: ask_ranmu :),

                "�޺�����"         : (: ask_me :)
        ]));

        setup();
	if (clonep()) {
                ob = unew(BINGQI_D("blade/jinnao"));
		if (ob) {
			destruct(ob);
                        ob = unew(BINGQI_D("blade/jinnao2"));
		}
              if (!ob) ob = unew(BINGQI_D("blade"));
		ob->move(this_object());
		ob->wield();
		carry_object("/d/shaolin/obj/xuan-cloth")->wear();
	}
}

#include "/kungfu/class/shaolin/xuan-ku.h"

int ask_shoudao()
{
	object me=this_player();
	if (me->query("family/family_name")!="������")
	{
		command("say �㲻�������ֵ��ӣ�����������\n");
		return 1;
	}
	if (me->query_skill("ranmu-daofa",1)<450)
	{
		command("say ��ȼľ������������450�����������Ŭ����\n");
		return 1;
	}
	if (me->query_skill("blade",1)<450)
	{
		command("say �����������������450�����������Ŭ����\n");
		return 1;
	}
	if (me->query_skill("xiuluo-dao",1)<450)
	{
		command("say ȼľ������Ҫ��ħ�Ĺ����������޵�����������450�����������Ŭ����\n");
		return 1;
	}
	if (me->query_skill("cibei-dao",1)<450)
	{
		command("say ȼľ�����̺���Ҵȱ����⣬��ȱ�����������450�����������Ŭ����\n");
		return 1;
	}
	if (time()-me->query("quest/sl/rmdf/shoudao/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�Ҫ֪����ҽ������Ƕ���\n");
		return 1;
	}
	if (me->query("quest/sl/rmdf/shoudao/pass"))
	{
		command("say ���ȼľ�ֵ������Ѿ��޳ɣ������鷳�Ħ���ˣ�\n");
		me->set("title",HIY"������"HIR"ȼľ��������"NOR);
		me->set("mytitle/quest/rmdtitle",HIY"������"HIR"ȼľ��������"NOR);
		return 1;
	}

	command("say ȼľ������������ʮ�������е����ļ���,���������ŵ��������ݺὭ����\n");
	command("say ��Ҳ�����Ǹո����ɵ����߾�����ѣ��������������ߵھž��磬��\n");
	command("say ��ƾ˫�ֵľ����������Է����������������������Ρ�\n");
	command("say ���ֹ���ǹ�����񲻿ɴﵽ��\n");
	command("say ���������׽�񹦴�ɣ�Ҳ������������Ԧ����\n");
	command("say ��ȻҲ��һ�ֽݾ������ǵ�����ת֮����\n");
	command("consider ");
    command("say �뵱�������¸�ɮ�Ħ��ƾ��һ����ʩչ��������ʮ�����������о�����������ȼľ����\n");
	command("say ���ĵ�ʱ�������ʩչȼľ���������ƻ����������ݺᣬ��Ȼ�����������ڹ�������ʽ���ˣ�\n");
	command("say �ⷨ��������һ�����˵ģ���������Ȥ�Ҿ�����һ�⣬��ȥ����������������ֽ�һ����\n");
	command("say ˵������һ���ջ�\n");
	command("hehe ");
	command("say �����������ޱߣ��Ѿ��󳹴�����ȥ��̣���������һ���ջ�\n");
	command("say �����书�ͻ��������븻Դ������أ�����Ҫ�����ϰ������Ч��\n");

	me->set_temp("rmdf/askku",1);
	return 1;
}

int ask_ranmu()
{
	object me=this_player();
	if (me->query("family/family_name")!="������")
	{
		command("say �㲻�������ֵ��ӣ�����������\n");
		return 1;
	}
	if (me->query_skill("ranmu-daofa",1)<250)
	{
		command("say ��ȼľ������������250�����������Ŭ����\n");
		return 1;
	}
	if (me->query("quest/sl/rmdf/ranmu/pass"))
	{
		command("say ���ȼľ�����Ѿ��޳ɣ����ؼ��������ˣ�\n");
		return 1;
	}
	if (me->query_skill("blade",1)<250)
	{
		command("say �����������������250�����������Ŭ����\n");
		return 1;
	}
	if (me->query_skill("xiuluo-dao",1)<250)
	{
		command("say ȼľ������Ҫ��ħ�Ĺ����������޵�����������450�����������Ŭ����\n");
		return 1;
	}
	if (me->query_skill("cibei-dao",1)<250)
	{
		command("say ȼľ�����̺���Ҵȱ����⣬��ȱ�����������450�����������Ŭ����\n");
		return 1;
	}
	if (time()-me->query("quest/sl/rmdf/ranmu/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�Ҫ֪����ҽ������Ƕ���\n");
		return 1;
	}

	command("say ȼľ������������ʮ�������е����ļ���,���������ŵ��������ݺὭ����\n");
	command("say ��Ҳ�����Ǹո����ɵ����߾�����ѣ��������������ߵھž��磬��\n");
	command("say ��ƾ˫�ֵľ����������Է����������������������Ρ�\n");
	command("say ���ֹ���ǹ������������������ǻ�����������������־����֮�����ɴﵽ��\n");
	command("say �����뽫ȼľ������һ��̨�ף���ȥ�����������ҳ��š�\n");
	command("say �������ѧϰ�����书���׵ġ�\n");

	me->set_temp("rmdf/askkuranmu",1);
	return 1;
}