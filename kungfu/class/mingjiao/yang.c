// yang.c ����
// 4/4/97 -qingyun
// 16.10.98 snowman
// Modify By River@sj 99.6
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
string dagger();
int ask_xiaoyao();
void create()
{
        set_name("����",({"yang xiao","yang","xiao"}));
        set("title", "���̹�����ʹ");
        set("nickname",WHT"��ң����"NOR);
        set("long", "���������̵Ĺ�����ʹ���ͷ�ң�ϳ���ң���ɵ����С�\n"+
                    "������һ���������Ȼ�������꣬������ȥ��ʮ��Ӣ��������\n");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen", -15000);
        set("str", 26);
        set("per", 29);
        set("int", 29);
        set("con", 27);
        set("dex", 30);         
        set("max_qi",24000);
        set("max_jing", 6000);
        set("eff_jingli", 6000);
        set("jiali", 200);
        set("combat_exp", 9700000);
        set("unique", 1);
        set("no_get",1);
		set("quest/mj/xyj/luanjian/pass",1);
		set("xyjf/jueji","pass");

        set("no_quest", 1);
        set_skill("sword",500); 
        set_skill("blade",450);
        set_skill("literate",300);
        set_skill("hand", 450);
        set_skill("strike", 450);
        //set_skill("hanbing-mianzhang", 420);
        set_skill("xiaoyao-jian", 500);
        set_skill("dodge",450);
        set_skill("force", 480);
        set_skill("piaoyi-shenfa", 450);
        set_skill("lieyan-dao",450);
        //set_skill("liehuo-jian",420);
        set_skill("shenghuo-shengong", 480);
        set_skill("parry", 450); 

        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("sword", "xiaoyao-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("blade", "lieyan-dao");
        map_skill("hand", "yingzhua-shou");
        //map_skill("strike", "hanbing-mianzhang");
       // prepare_skill("strike", "hanbing-mianzhang");
        //prepare_skill("hand","yingzhua-shou");
        create_family("����",35,"ʹ��");

        set("inquiry", ([
                "ذ������" : (: dagger :),
                "book" : (: dagger :),
                "������" : (: ask_me :),
			    "��ң������" : (: ask_xiaoyao :),
                "�����׻�":"��˵�������˴��й�ѧ�����ҩ֮�����Ƴ�һ�ְ�����\n"
                        "�����������׻𵯡����в����Ի�ҩ����ǿ�����ɻ������䡣\n",
        ]));

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: exert_function, "shenghuo" :),
			    (: perform_action, "xiao" :),
				(: perform_action, "xiaoyao" :),
				(: perform_action, "luanjian" :),


        }));
        setup(); 
        if( random(10) > 5)
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object("/d/mingjiao/obj/white-cloth")->wear();
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
        if(fam["master_name"] == "��ң"){
                command("say ��ң���ɲ������ң���Ȼ�����������æ�������ʱ��������ɡ�");
                ob->set("title", this_object()->query("title")+"���µ���"); 
                command("recruit " + ob->query("id"));
                return;
                }
        if (fam["generation"] > (my_fam["generation"] + 2)){
                command("say ���ҿ���Ӧ��������λ��������ѱ���ѧ��������");
                return;
                }
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 300) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ������300��Ҫ�����ҡ�"); 
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ����ʥ�����϶��µ㹦��");
                return;
                }
        if ((int)ob->query_int() < 40) {
                command("say ��ң���ɵ��书�����ӣ�Ҫѧ����Щ�书���ǵ��м��ߵ����ԡ�");
                command("say �����Է��治��40�㣬"+RANK_D->query_respect(ob)+"�Ƿ񻹲�����");
                return;
                }
        command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
        command("say ��л������ӣ����������ֵ�һ���ģ�Ϊ�������壬�������̷�����ɡ�");
        command("recruit " + ob->query("id"));
        ob->set("title", HIW+this_object()->query("title")+"���µ���"NOR);
}
 
void init()
{
        object me, ob;
        mapping fam;
        ::init();
        ob = this_player();
        me = this_object();        
	 if(interactive(ob) && !wizardp(ob)
	 && base_name(environment(me))=="/d/mingjiao/longwang"
	 && ((fam = ob->query("family")) && fam["family_name"] != "����" )){
		command("say ���������̵��صأ���˵�����ˣ�������������Ҳ��������������Ͽ��뿪�˵أ�");
		command("consider "+ob->query("id"));  
		remove_call_out("kill_ob");
		call_out("kill_ob", 5, ob); 
	}
	if(interactive(ob) && ob->query_temp("mj_jiaozhu"))           
		command("nod "+ob->query("id"));   
	else 
		command("hehe "+ob->query("id"));      
}

string dagger()
{
	mapping fam = this_player()->query("family");
	object ob;        
	if(!fam || fam["family_name"] != "����")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";

	if(this_player()->query_skill("dagger",1) > 100)
		return "���ذ���Ѿ���һ�������ˣ��Ȿ�����ûʲô�ã������������˰�";        

	if(! this_player()->query_skill("jiuyang-shengong", 1))
	if(this_player()->query_skill("shenghuo-shengong", 1) < 100)
		return "�������̵�ʱ���ж̣�����ʱ�������ɡ�";
	ob = unew("/clone/book/dagger-book");
	if(!clonep(ob))
		return "�������ˣ��ҵġ�ذ�����ۡ��Ѿ������������ˡ�";   
	if(clonep(ob) && ob->violate_unique()){
		destruct(ob);
		return "�������ˣ��ҵġ�ذ�����ۡ��Ѿ������������ˡ�";  
	}      
	ob->move(this_player());
		return "�ðɣ�������������ġ�ذ�����ۡ����͸����ˡ�";
}

string ask_me()
{ 
	mapping fam; 
	object ob, *clone;
	int i, j;

	if(!(fam = this_player()->query("family")) || fam["family_name"] != "����")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";
	if(! this_player()->query_skill("jiuyang-shengong", 1))
	if(this_player()->query_skill("shenghuo-shengong", 1) < 100)
		return "�������̵�ʱ���ж̣�û��Ȩ��ʹ�������";
	if(!this_player()->query_skill("shenghuo-lingfa"))
		return "���ֲ�ʹ��������������ʲô��";
	ob=present("tieyan ling",this_player());
	if(ob && ob->query_amount() >= 2)
		return "�����϶��Ѿ���ô���ˣ���Ҫ���ʲô��";
	ob=unew(BINGQI_D("tieyan-ling"));        
	if(!clonep(ob)) return "�������ˣ��������Ѹ�ȫ������ȥ�ˡ�"; 
	i = ob->query("unique");
	clone = filter_array(children(base_name(ob)), (: clonep :));
	j = sizeof(clone);
	while (j--) if (!clone[j]->query("clone_by_wizard")) i--; 
	if(clonep(ob) && i < 0){
		destruct(ob);
		return "��Ǹ���������ˣ��������Ѹ�ȫ������ȥ�ˡ�";
	}
	ob->move(this_player());
	return "�ðɣ���������������ȥ�ɣ����㲻Ҫ����Ϊ�񣬶�෢չ�����̽��ڡ�";
}

int ask_xiaoyao() 
{
	object me = this_player();
	int i,j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й���ң�������������\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	//��ͨ�������
	if(me->query("family/family_name")!="����")
	{
		command("heng "+me->query_id());
		command("say �����������ʲô��ϵ���Ͻ����ҹ���");
		return 1;
	}
	if(me->query("xyjf/jueji")=="pass")
	{
		command("heng "+me->query_id());
		command("say ���Ѿ��⿪�����⣬����ǲ��ô��");
		return 1;
	}
	if(me->query("xyjfjj/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("xyjfjj/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�����ɣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("xiaoyao-jian",1)<300)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�Ľ�����û��С�ɣ����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}    
	me->set("xyjfjj/time",time());
	me->set("xyjfjj/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("say ��ң����������ң���ɵľ�������Ȼ����������Ҿ�˵����������������û����������ˡ�");
   	command("say �������ǲ��Ӷ��ڻ��ͨ�������κ��书���ﵽһ���������������������һ��");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));

	j = 18;
    if(me->query("m-card-vip")) j =  16;
    if(me->query("y-card-vip")) j =  12;
    if(me->query("buyvip"))     j =  8;
	  
	i= random(j); 
	if(i<5 && random(me->query("kar"))>=25)
	{
		tell_object(me,HIW"\n�㰴�����е�ָ�㣬����ң�������������ƺ���Щ�ĵá�\n"NOR);
		tell_object(me,HIC"\n������н��������ʽ�ӿ�ʼ������һ·�����������������硣\n"NOR);       
		tell_object(me,HIG"\n���������������ǹ��ꪣ����������ң���������ذ���ʹ̡�\n"NOR);
		tell_object(me,HIR"\n�����������йٱʣ��㡢�����ࡢ���������ֱ�����ֱָޡ�\n"NOR);   
	    tell_object(me,HIY"\n��������ֻ������ߣ���æ�����Ա�����������������֮�������ҵ�������\n"NOR);
		tell_object(me,HIB"\n˲���������˶�ʮ������У�ÿ����о���������ʽ��һ����ʮ������ʽ��\n"NOR);
        tell_object(me,HIC"\n���Ѿ�ѧϰ�����������е���ң���ľ�����\n"NOR);
		
		command("look "+me->query("id"));
		command("chat "+me->query("id")+"�Ѿ�������ҵ��洫�����뽭��ͬ���Ժ���չ�����λ�ֵܡ�");
		command("haha "+me->query("id"));
		command("chat* congra"+me->query("id"));
		me->set("xyjf/jueji","pass");
		//me->set("title",HIC"");
		log_file("quest/xiaoyaojian", sprintf("%8s(%8s) ʧ��%d�κ󣬳���������ң���ľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("xyjfjj/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("xyjfjj/fail",1);
		command("sigh ");
		tell_object(me,HIY"���������е�ָ�㣬��Ȼ��������ң������ʽ�����⣬���Ƕ���ң����������������ȫȻ����Ҫ�졣\n\n"NOR);
		command("poor "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/xiaoyaojian", sprintf("%8s(%8s) ��ң����������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("xyjfjj/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}