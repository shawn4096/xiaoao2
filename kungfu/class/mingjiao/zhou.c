// zhou.c �ܵ�
// Modify By River@sj 99.06
// Modify by Looklove@sj 2000/9/30



#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_blade();
string ask_canqu();

void create()
{
        object weapon;
        set_name("�ܵ�", ({ "zhou dian","zhou","dian" }) );
        set("title", "������ɢ��");
        
        set("gender", "����");
        set("age",52);
        set("long", "������������ɢ��֮һ���ܵߡ�\n");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("shen_type",0);
        set("combat_exp", 4600000);
        set("unique", 1);

        set_skill("blade",450);
        set_skill("force",450);
        set_skill("dodge",450);
        set_skill("hand", 450);
	    set_skill("parry", 450);
        set_skill("piaoyi-shenfa",450);
        set_skill("shenghuo-shengong",450);
        set_skill("lieyan-dao",450);
        set_skill("yingzhua-shou",450);
        map_skill("hand","yingzhua-shou");
        map_skill("force","shenghuo-shengong");
        map_skill("dodge","piaoyi-shenfa");
        map_skill("blade","lieyan-dao");
        map_skill("parry","lieyan-dao");
        prepare_skill("hand","yingzhua-shou");

        create_family("����",36,"ɢ��");

        set("max_qi",15000);
        set("max_jing",5200);
        set("jiali",200);
        set("eff_jingli",5200);
        set("inquiry", ([
                "�赶"     : (: ask_blade :),
			     "���Ҳ���"     : (: ask_canqu :),

                "���浶" : "�����ҵ�������������ã����Խ���㡣\n",
                ]));
        setup();

        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
        if (clonep()){
                weapon = unew(BINGQI_D("blade/qingyan-dao"));
                if(!weapon) weapon=new(BINGQI_D("blade"));
                weapon->move(this_object());
                weapon->wield();
        }
}

void init()
{
	::init();
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
string ask_blade()
{ 
        object blade,me,ob;
        me = this_player(); 
        ob = this_object();

        if ( me->query("combat_exp") < 100000 )
        return RANK_D->query_respect(me)+"�Ĺ���̫�����㣬����Ҳ����ס������";
        if ( present("qingyan dao", me)|| me->query_temp("qydao"))
                return RANK_D->query_respect(this_player()) + 
                "��ֻ��һ�ѣ��Ѿ����������";
        if ( blade=present("qingyan dao", ob))
        command("give qingyan dao to "+me->query("id"));
        if(!objectp(blade))   blade = unew(BINGQI_D("blade/qingyan-dao"));
        if(!objectp(blade))   return "��Ǹ��������浶���Ѿ���������ˡ�"; 

        blade->move(me);
        blade = unew(BINGQI_D("blade"));
        blade->move(this_object());
        me->set_temp("qydao",1);
        command("wield dao"); 
        return "��Ҷ��ǽ���ͬ������������,������ȥ�á�";
         
}
string ask_canqu()
{ 
        object me,ob;
		int i,j;
        me = this_player(); 
        ob = this_object();

        if ( me->query("family/family_name")!="����" )
        return RANK_D->query_respect(me)+"�������̵��ӣ�����͵ѧ�����书��\n";
        
		if (me->query_skill("lieyan-dao",1)<200)
                return RANK_D->query_respect(this_player()) + 
                "������浶�ȼ�����200�������Ͻ�����ȥ��";
        if (me->query("quest/mj/lyd/canqu/pass"))
        {
			return "���Ѿ��⿪�ˡ����Ҳ�������������ؾ�\n";
        }

       if (time()-me->query("quest/mj/lyd/canqu/time")<86400)
        {
			return "������̫Ƶ���ˣ����������С�\n";
        }
	   message_vision(HIY"$N����$n������˵�������뵱���Ҵ����̺���Ӫ��лʨ��������������һս\n"
					"��ν���Ķ��ǣ��Һ��н�����ѹȺ�ۣ��������������롣ÿ�������𵱳��ڷ�ħȦ\n"+
				   HIM"������������һս��������ǵ�ʱ���Ե�������Ϯ������ע�������������˵��\n"NOR,this_object(),me);
	
 
		i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		command("say ������������̽��壬��ζ��һ�������������һ𣬷��Ҳ�����ԭ���Ǳ�������һ������\n");
		command("say ֻҪ����������������һ�У������վ����ǻᵨ���ģ�\n");
		
		command("pat "+me->query("id"));
		command("laugh ");
	    message_vision(HIR"$N����$n������˵��������Ҫ�����״������⣬Ҫ�ú����ҵĿھ�,�������\n"
					RED"�����һ�\n"+
					HIG"���Ҳ���\n"+
					YEL"����λ�\n"
					MAG"����ο�\n"+
					BLU"Ϊ�Ƴ���\n"
					WHT"Ω������\n"
					CYN"ϲ�ֱ���\n"
					HIY"�Թ鳾��\n"
					HIW"��������\n"
					HIG"�ǻ�ʵ��\n"
					HIM"��������\n"
					HIR"�ǻ�ʵ��\n"
				    HIC"...........��\n"NOR,this_object(),me);
		message_vision(HIR"\n\n�ܵ�Խ˵����Խ�Ǻ��߿��������ϵ�����ȴ���������Ӳ��٣�\n"NOR,me);
		if( i<5
			&& me->query("kar")<31
			&& j >= 24 ) 
		{
			tell_object(me,HIY"\n�������ܵߵ�����ָ�㣬�����������Լ��������浶�������ĵã�����ӡ�ա�\n"NOR);
			tell_object(me,HIG"\n���к�����������ʶ���������������Լ����ϻ��˼��£��漴Ҳ�����ܵ�����������\n"
								RED"�����һ�\n"+
					HIG"���Ҳ���\n"+
					YEL"����λ�\n"
					MAG"����ο�\n"+
					BLU"Ϊ�Ƴ���\n"
					WHT"Ω������\n"
					CYN"ϲ�ֱ���\n"
					HIY"�Թ鳾��\n"
					HIW"��������\n"
					HIG"�ǻ�ʵ��\n"
					HIM"��������\n"
					HIR"�ǻ�ʵ��\n"

							 HBYEL+"��ϲ�㣡����ǧ������������������ŷ��Ҳ������������÷��š����д�ϲ��\n"NOR);
			me->set("quest/mj/lyd/canqu/pass",1);
			log_file("quest/lydcanqu", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�����浶���Ҳ�������,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/mj/lyd/canqu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			command("haha"+me->query("id"));		
			
			return "��ϲ�����������浶���Ҳ��������ɹ�!\n";
			
		}	
	   else
		{
			log_file("quest/lydcanqu", sprintf("%8s(%8s) �������浶���Ҳ�������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/mj/lyd/canqu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"�������ܵߵ�ָ�㣬���Ƕ����浶���Ҳ����İ���ȫȻ����Ҫ�졣\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/mj/lyd/canqu/fail",1);
			me->set("quest/mj/lyd/canqu/time",time());
			me->start_busy(1+random(3));
			
			return "�ǳ��ź������������浶���Ҳ���ʧ��"+me->query("quest/mj/lyd/canqu/fail")+"�Ρ�\n";
		}
				
		
		return "����...\n";
         
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


#include "5san_app.h";

