// fan.c ��ң
// 4/4/97 -qingyun
// 16.10.98 snowman
// Modify By River@sj 99.6
//modify by looklove@sj 2000.11
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_luanjian();
void create()
{
        set_name("��ң",({"fan yao","fan","yao"}));
        set("title","���̹�����ʹ");
        set("nickname",WHT"��ң����"NOR);
        set("long", "���������̵Ĺ�����ʹ�������кϳ���ң���ɵķ�ң��\n"+
                    "������һ���������Ȼ�������꣬������ȥ��ʮ��Ӣ��������\n");
        set("age", 46);
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 36);
        set("per", 28);
        set("int", 29);
        set("con", 27);
        set("dex", 30);
        set("max_qi", 25000);
        set("max_jing", 4500);
        set("eff_jingli", 4500);
        set("jiali", 200);
        set("combat_exp", 9700000); 
        set("unique", 1);
		set("quest/mj/xyj/luanjian/pass",1);
		set("xyjf/jueji","pass");

        set_skill("sword",500); 
        set_skill("dodge",450);
        set_skill("force", 500);
        set_skill("blade",400);
        set_skill("literate",250);
        set_skill("hand",450);
        //set_skill("strike",420);
        //set_skill("hanbing-mianzhang",170);
        set_skill("yingzhua-shou",450);
        set_skill("piaoyi-shenfa", 450);
        set_skill("shenghuo-shengong", 500);
        set_skill("lieyan-dao",400);
        set_skill("xiaoyao-jian",500);
        set_skill("parry", 450);

        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("sword", "xiaoyao-jian");
        map_skill("parry", "lieyan-dao");
        map_skill("blade", "lieyan-dao");
        map_skill("hand", "yingzhua-shou");
       //map_skill("strike", "hanbing-mianzhang");
       // prepare_skill("strike", "hanbing-mianzhang");
        prepare_skill("hand","yingzhua-shou");

        create_family("����",35,"ʹ��");

        set("inquiry", ([
                 "���������" : (: ask_me :),
				"�ҽ���" : (: ask_luanjian :),
        ]));
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: exert_function, "shenghuo" :),
			    (: perform_action, "xiao" :),
				(: perform_action, "xiaoyao" :),
				(: perform_action, "luanjian" :),

        }));
        setup();
        //if ( random(10) > 5 )
        carry_object(BINGQI_D("sword"))->wield();
        carry_object("/d/mingjiao/obj/white-cloth")->wear();
}


void init()
{
	::init();
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");
        mapping my_fam = me->query("family");
        if(!fam || fam["family_name"] != "����"){
                command("say "+RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
                }
        if(fam["master_name"] == "���޼�"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"���ǽ����״����ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��"); 
                return;
                }
        if(fam["master_name"] == "����"){
                command("say ��ң���ɲ������ң���Ȼ����������·�æ�������ʱ��������ɡ�");
                ob->set("title", this_object()->query("title")+"���µ���");
                command("recruit " + ob->query("id"));
                return;
                }
        if (fam["generation"] > (my_fam["generation"] + 2)){
                command("say ���ҿ���Ӧ��������λ��������ѱ���ѧ��������");
                return;
                }
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 300) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ��"); 
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ����ʥ�����϶��µ㹦��");
                return;
                }
        if ((int)ob->query_int() < 40) {
                command("say ��ң���ɵ��书�����ӣ�Ҫѧ����Щ�书���ǵ��м��ߵ����ԡ�");
                command("say �����Է��棬"+RANK_D->query_respect(ob)+"�Ƿ񻹲�����");
                return;
                }
        command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
        command("say ��л������ӣ����������ֵ�һ���ģ�Ϊ�������壬�������̷�����ɡ�");
        command("recruit " + ob->query("id"));
        ob->set("title", HIW+this_object()->query("title")+"���µ���"NOR);
}

string ask_me()
{
	mapping fam; 
	object ob, *clone;
	int i, j;

	if(!(fam = this_player()->query("family")) || fam["family_name"] != "����")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";

	if (! this_player()->query_skill("jiuyang-shengong"))
	if(this_player()->query_skill("shenghuo-shengong", 1) < 50)
		return "�������̵�ʱ���ж̣������������㻹�����ʸ�ʹ�á�";

	if(this_player()->query_temp("marks/��1"))
		return "�㲻�Ǹ����˺��������������ô��Ҫ��";

	if(present("heiyu duanxugao", this_player()))
		return "�����ϲ��Ǵ��ź������������ô��Ҫ��";

	if ((int)this_player()->query("eff_qi") == (int)this_player()->query("max_qi"))
		return "�����ڲ���Ҫ�ú�������ࡣ";

	ob=unew(MEDICINE_D("heiyu"));        
	if(!clonep(ob)) return "�������ˣ�����������Ѹ�ȫ������ȥ�ˡ�"; 
	i = ob->query("unique");
	clone = filter_array(children(base_name(ob)), (: clonep :));
	j = sizeof(clone);
	while (j--) if (!clone[j]->query("clone_by_wizard")) i--; 
	if(clonep(ob) && i < 0){
		destruct(ob);
		return "��Ǹ���������ˣ�����������Ѿ�û���ˡ�";
	} 
	ob->move(this_player());
	this_player()->set_temp("marks/��1",1);
	return "�ðɣ���к�������������ȥ�ðɡ�";
}

int do_kill(string arg)
{
	object ob,ob2; 
	object me = this_player();
	ob2 = this_object();

	if (!arg) return 0;
	ob = present(arg, environment(me));
	if (ob == this_object() || ob == me) return 0;
	if (!ob || !ob->is_character()) return 0;
        
	if (userp(ob) && ob->query("family/family_name") == "����") {
                if (me->query("family/family_name") == "����") { 
			message_vision(ob2->name()+"��$N�ȵ�����Ϊ���̵��ӣ���Ȼɱ�Լ���ͬ�ţ��������㣡\n", me);
		}
		else {
			message_vision(ob2->name()+"��$N�ȵ����󵨿�ͽ����Ȼ����������Ұ��\n", me);
			kill_ob(me);
		}
		me->set("vendetta/����", 1);
		return 1;
	}
	return 0;
}


string ask_luanjian()
{
	mapping fam; 
	object me;
	int i, j;
	me=this_player();
	if(!(fam = this_player()->query("family")) || fam["family_name"] != "����")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��\n";

	if ( this_player()->query_skill("sword",1)<300) 
		return RANK_D->query_respect(this_player())+"��Ļ�����������300��Ŭ����ϰȥ��\n";

	if(this_player()->query_skill("xiaoyao-jian", 1) < 300)
		return "�����ң��������300��Ŭ����ϰȥ��\n";

	if(time()-me->query("quest/mj/xyj/luanjian/time")<86400)
		return "������ڿ죬���Ǵ����̵ĺõ���!\n";
	if(me->query("quest/mj/xyj/luanjian/pass"))
		return "���Ѿ��⿪����ң���ҽ��������Ǵ����̵ĺõ���!\n";
	j=18;
	if(me->query("m-card-vip")) j =  15;
    if(me->query("y-card-vip")) j =  12;
    if(me->query("buyvip"))     j =  8;
	i=random(j);
	command("say ���ҽ��������Ҷ�����ĵã�����ҪѧϰҪ�ú������ˡ�\n");
	command("say ѧ�������书�ľ����������ѧ����Ҫ�����Ӳ���ȡ��㲩֮�⡣\n");
	command("say �����书���������ԣ���û�кõ�����Ҳ���С�\n");
	command("say �����á�\n");
	if(i<3 && random(me->query("kar"))>=23)
	{
		tell_object(me,HIY"\n�㰴�շ�����ָ�㣬����ң�����ҽ��������ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIY"\n�㽫������������ݺ���ǰ�Լ���ѧ�໥ӡ֤���漴�����̲�ס������Ц��\n"NOR);
		tell_object(me,HIG"\n��ϲ������ǧ����࣬���ڽ⿪��ң�����ҽ������ܡ�\n"NOR);
     //   tell_object(me,HIR"\n���Ѿ���Ǭ����Ų�Ƶ��߲��񹦳����ڻ��ͨ��\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("quest/mj/xyj/luanjian/pass",1);	
		log_file("quest/xyjluanjian", sprintf("%8s(%8s) ʧ��%d�κ󣬳���������ң���ҽ����ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/mj/xyj/luanjian/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/mj/xyj/luanjian/fail",1);
		command("poor ");
		tell_object(me,HIY"�����˷�����ָ�㣬��Ȼ��˵�������书�İ��أ����Ƕ����еİ���ȫȻ����Ҫ�졣\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->set("quest/mj/xyj/luanjian/time",time());
		log_file("quest/xyjluanjian", sprintf("%8s(%8s) ��ң���ҽ�������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/mj/xyj/luanjian/fail"),i,me->query("combat_exp")) );
	}
	return "�ţ�����ң�����ҽ������Ҷ�����ĵã���Ҫ�úõĴ�����������Ҫ��������ң���ɵ�������\n";
	
}
