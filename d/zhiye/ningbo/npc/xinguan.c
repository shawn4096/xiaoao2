// xinguan.c �Ĺ۴�ʦ

//�ȴ���������
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;

string ask_me();

void create()
{
        object ob;
        set_name("�Ĺ۴�ʦ", ({
                "xinguan dashi",
                "xinguan",
                "dashi",
        }));
        set("long",
				"����������ͯ�������Ĺ۴�ʦ��һ��ȱ����������������ǽ����г�\n"
                "���������ˣ��������ü����һϮ��˿�ػ����ġ�����ļ��ݣ�\n"
                "���ָ���צһ������˫Ŀ΢�գ�һ��û����ɵ�ģ����\n"
        );


        set("nickname", HIY"��ͯ������"NOR);
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 28000);
        set("max_jing", 10000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 200);
        set("combat_exp", 8000000);
        set("score", 500000);

        set_skill("force", 450);
        set_skill("yijin-jing", 450);
        set_skill("dodge", 450);
        set_skill("shaolin-shenfa", 450);
        set_skill("parry", 450);
        set_skill("claw", 450);
        set_skill("blade", 450);
        set_skill("finger", 450);
        set_skill("cibei-dao", 450);
        set_skill("yizhi-chan", 450);
        set_skill("longzhua-gong", 450);
        set_skill("buddhism", 150);
        set_skill("literate", 250);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("claw", "longzhua-gong");
        map_skill("finger", "yizhi-chan");
        map_skill("blade", "cibei-dao");
        map_skill("parry", "cibei-dao");

        prepare_skill("finger", "yizhi-chan");
        prepare_skill("claw", "longzhua-gong");

      //  create_family("������", 36, "����");

        set("inquiry", ([
                "�ȱ�������"       : (: ask_me :),
           //     "�޺�����"         : (: ask_me :)
        ]));

        setup();
        if (clonep()) {                
                ob = unew(BINGQI_D("blade"));               
                if (!ob) ob = unew("/clone/weapon/blade");
                ob->move(this_object());
                ob->wield();
                carry_object("/d/shaolin/obj/xuan-cloth")->wear();
        } 
}


int ask_me()
{
	int i,j;
	object me=this_player();

	if (!me->query_temp("cbd/askxuanbei"))
	{
		command("say �������ԩ�޳�Ϊ����������ɧ����ɮ��\n");
		return 1;
	}
	if (me->query("quest/sl/cbd/pass"))
	{
		command("say ���Ѿ���ϰ�˴ȱ�����������Ҫ����ɧ����ɮ�ˣ�\n");
		me->set("title",YEL"��ͯ�´ȱ�������"NOR);
		me->set("mytitle/quest/ttscbdtitle",YEL"��ͯ�´ȱ�������"NOR);
		return 1;
	}
	if (time()-me->query("quest/sl/cbd/time")<86400)
	{
		command("say ��̫�ڿ��ˣ���ɮ�Ҳ���ɧ�ţ�\n");
		return 1;
	}
	j = 18;
    if(me->query("m-card-vip")) j =  16;
    if(me->query("y-card-vip")) j =  13;
    if(me->query("buyvip"))     j =  8;
	if (me->query("class")=="bonze")
	     i=random(j-2);
	  else i= random(j);
 
    if(i<3 && random(me->query("kar"))>=25)
	 {
		tell_object(me,HIG"\n�㰴���Ĺ۴�ʦ��ָ�㣬�Դȱ����������������ƺ���Щ�ĵá�\n"NOR);
       
		tell_object(me,HIY"\n������ǧ����࣬���ڵó���Ը�����ȱ������ڻ��ͨ��\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/sl/cbd/pass",1);
		me->set("title",YEL"��ͯ�´ȱ�������"NOR);
		me->set("mytitle/quest/ttscbdtitle",YEL"��ͯ�´ȱ�������"NOR);
		me->start_busy(1);
		log_file("quest/slcibeidao", sprintf("%8s(%8s) ʧ��%d�κ󣬳�������ȱ������ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/sl/cbd/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/sl/cbd/fail",1);
		me->set("quest/sl/cbd/time",time());
		command("buddha ");
		tell_object(me,HIY"�������Ĺ۴�ʦ��ָ�㣬��Ȼ�����˴ȱ������İ��أ����ǶԴȱ�����������������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/slcibeidao", sprintf("%8s(%8s) �ȱ���������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/sl/cbd/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;

  

}

