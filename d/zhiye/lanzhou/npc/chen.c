// By Spiderii fix bug
// chen.c
inherit NPC;
#include <ansi.h>;
string cxz();
void init()
{
        object me = this_player();
        if (me->query_temp("thd/onquest")==2) { 
           message_vision(HIY"$N�����ڷ�˫ɷ�����Ͷ񣬶�ʱ����ѥ�Ե�ذ��(bishou)��\n"NOR,me);
           add_action("do_chou","chou");
        }
}

void create()
{
        set_name( "������" ,({ "chen xuanfeng", "chen" }));
        set("title", "�ڷ�˫ɷ");
        set("nickname", HIY"ͭʬ"NOR);
        set("gender", "����");
        set("age", 35);
        set("long",
            "�����ǻ�ҩʦ�Ķ����ӣ���Ũü���ۣ���������������׳����ֻ��\n"
            "��ɫ΢΢���ơ�\n");
        set("attitude", "aggressive");
        set("str", 37);
        set("int", 32);
        set("con", 35);

        set("unique", 1);
        set("no_quest", 1);
        set("max_qi",33500);
        set("qi",33500);
        set("max_jing",5000);
        set("neili", 34500);
        set("max_neili", 34500);
        set("jiali", 250);
        set("shen",-50000);

        set("combat_exp", 9500000);

        set_skill("claw", 450);
		set_skill("strike", 450);
        set_skill("force", 450);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("leg", 450);
        set_skill("jiuyin-baiguzhua", 450);
        set_skill("bihai-chaosheng", 450);
        set_skill("suibo-zhuliu", 450);
        set_skill("xuanfeng-tui", 450);
		set_skill("cuixin-zhang", 450);
		set("quest/jiuyin2/cuixin/pass", 1);
		
        map_skill("strike", "cuixin-zhang");
        map_skill("force", "bihai-chaosheng");
        map_skill("parry", "jiuyin-baiguzhua");
        map_skill("dodge", "suibo-zhuliu");
        map_skill("claw", "jiuyin-baiguzhua");
        map_skill("leg", "xuanfeng-tui");
        prepare_skill("strike", "cuixin-zhang");

        create_family("�һ���", 2, "�������");
        set("inquiry", ([
           "ͭʬ":     "�����ϵ��˶���ô���ҵģ����²��£�����������",
           "��а":     "������ʦ���Ĵºš�",
           "����":     "�������ʦ�����ĸ���֮һ���Ǹ��϶��ס�ڰ���ɽ��",
           "�ϵ�":     "����ү�ѳ��ҵ�����ȥ�ˣ�������һ�ơ�",
           "��ؤ":     "��ؤͳ����ԭ��ؤ�������Ϊǿ��",
           "���߹�":   "���߹��书��ǿ�����ҽ̻������С������ʮ���ƣ��ɺޣ�",
           "����":     "������ʦ���Ķ�Ů�����ǵ������ԡ�",
           "÷����":   "�����ҵ�ʦ�ã�Ҳ���ҵ����ҡ�",
           "������":   "��������ô�����ǰ׳հ���",
		   "������": (: cxz :),
           "��ҩʦ":   "������ʦ����"]) );
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
}


string cxz()
{
	object me = this_player();
	object ob = this_object();
	object kulou;
	int exp, time, night;
	mixed *local;
	//night = 0;
	//local = localtime(time() * 60);
	//if (local[2] < 5 || local[2] >= 19) night = 1;	
	
	if(QUEST_D->queryquest(me,"jiuyin2/cuixin"))		
	{
		if( QUEST_D->queryquest(me,"jiuyin2/jybgz"))
		{
			QUEST_D->setmytitle(me,"jydowntitle",HIY"�����澭��"HIB"�׹Ǵ���"NOR);			
			me->delete("mytitle/quest/cxztitle");
			me->delete("mytitle/quest/jybgztitle");
		    return RANK_D->query_respect(me) + "�����Ѿ�ѧ������µ�ȫ�����У��ֺιʿ�����Ц�أ�";			
		}
		else
		{
	   QUEST_D->setmytitle(me,"cxztitle",HIY"ͭʬ������"NOR);		
		return RANK_D->query_respect(me) + "�����Ѿ��õ��������ؾ����ֺιʿ�����Ц�أ�";
		}
	}
	
	if ( me->query("shen") > 0) return "�㲻���ĺ����������ѧ������Ƶ����С�\n";
	
	if( me->is_busy() || me->is_fighting() ) return "����æ���ء�\n";

	if( ob->is_busy() || ob->is_fighting() ) return ob->name()+"��æ���ء�\n";	    
    
	

    if( me->query_skill("cuixin-zhang", 1) < 300 )
		return RANK_D->query_respect(me) + "����Ĵ��������費�����޷������ҵľ�Ҫ���ڣ�";
 
	
	if (QUEST_D->queryquesttime(me,"jiuyin2/cuixin"))
		return "�ţ��㲻�Ǹ�����̹����𣿻�����Ŭ����ʱ��ɣ�";
	
	
		me->start_busy(1);
		message_vision(CYN"$N����$n˵��������ǰ��ָ��"+RANK_D->query_self(me)+"������Ҫ�壡��\n"NOR, me, ob);	
	
	COMBAT_D->do_attack(ob, me, 0, 1);	
	COMBAT_D->do_attack(ob, me, 0,1);	
	COMBAT_D->do_attack(ob, me,0, 1);
	
	message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	
	//if( random(me->query("kar")) > 28 && random(10)==3) {	// �����Դ
	//1������������Ʒ�ݲ����룬80������ά�������������0�������Ƹ�quest�������������������ж�����������
	  
	   if (QUEST_D->questing(me,3,80,0,"jiuyin2/cuixin")) {	
	   
			message_vision(HIW"$NͻȻ��׽ס����˲���һĻ����������������Ƶ�Ҫ�塣\n", me);
			tell_object(me, BYEL"��ϲ�㣬����" + NATURE_D->game_time() + "�����˴����Ƶ�Ҫ�塣\n"NOR);
			
			QUEST_D->setmytitle(me,"cxztitle",HIY"ͭʬ������"NOR);	
			
			log_file("quest/cuixinzhang",sprintf("%-18sʧ�ܶ�κ󣬴ӳ����紦ѧ�����������⣬����%d��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",me->query("kar")), me);
			return "��ϲ����ϲ��";
		}
		else {
			message_vision(HIC"$Nҡ��ҡͷ�������������Ǻ����ѵġ���˵�գ������̾�˿�����\n", me);
			
			return "��̫û���ã����°ɡ�";
		}	
	
	
}

void kill_ob(object me)
{
        object ob=this_object();
		object mei;
		
		mei = present("mei chaofeng",environment(me));
	if (mei) {
		mei->force_me("guard chen xuanfeng");
		mei->kill_ob(me);
	}		
		
        command("say �����ҵľ����澭��û��ô���ף�");
        message_vision(HIY"��������$N�������У���·������ȥ��\n\n"NOR,me);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        command("out");
        ::kill_ob(me);
}

void do_dest(object ob)
{
	::die();
}

int do_chou(string arg)
{
        object me = this_player();
        object ob = this_object();
        object obj;
        string msg;
        if (!arg||arg!="bishou")
                return notify_fail("ʲô��\n");
        if (me->query_temp("thd/onquest")!=2)
                return notify_fail("ʲô��\n");         
        if(arg=="bishou"&&me->query_temp("thd/onquest")==2)
        {
                msg = HIR"$N�����ڷ�˫ɲϮ��������һ�������ذ�׺��һ���������\n";
                msg+= HIR"��������Цһ������$N��ͷ����Ѩһ����$N��һ������Ȼ���ò���\n";
                msg+= HIR"���Ķ����ϣ�\n\n"NOR;
                msg+= HIY"���������$N����������������\n\n"NOR;
                msg+= HIC"÷����ҽ�һ�����������������㹥����\n"NOR;
                        if (!objectp(obj = present("mei chaofeng",environment(me)))) {
                                call_out("do_dest",1,ob);
                                return 1;
                        }
                obj->set_temp("target",me->query("id"));
                message_vision(msg, me);
                me->set_temp("thd/onquest",3);
                ob->die();
                return 1;
         }
}

void die()
{
	object me = query_temp("last_damage_from");
	object skin;
	int i, time;
	    
		if (!objectp(me)) {
			::die();
		     return;
		}

        i = me->query("combat_exp") - 1000000;
		i /= 1000000;

		
		if(QUEST_D->queryquesttime(me,"jiuyin2"))		
   		{
				::die();
				return;
		}

	   if (me->query("quest/jiuyin2/fail") >= 3 && me->query("registered") < 2)
	   {
		::die();
		return;
    	}		
		
			
      //�����ü�quest����
	    if(QUEST_D->queryquest(me,"jiuyin2") || QUEST_D->easy_questing(me,5,"jiuyin2"))
        {
            skin = unew(__DIR__"../obj/jiuyin-book2");
		     if(!clonep(skin))
			         {
						
			             ::die();
			             return;
		                    }
		    message_vision(HIY"\n$N����������������һƬƤ�˳������������\n"NOR,me);
		    skin->set("owner", me->query("id"));
		    skin->move(me);
			
		if(!QUEST_D->queryquest(me,"jiuyin2"))
			
		
		::die();
		return;
	    }
	  

		me->set("quest/jiuyin2/combat_exp", me->query("combat_exp"));
		
	::die();
	return;
}
