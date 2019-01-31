// NPC: /d/huashan/npc/laodenuo.c
// Date: Look 99/03/25
// Lklv Modify at 2001.10.18
// By Spiderii@yt�޸�ٺ»
#include <ansi.h>
inherit NPC;
//inherit F_MASTER;

string ask_me(object who);
int ask_gold(object who);

void create()
{
        set_name("�͵�ŵ", ({ "lao denuo", "lao", "denuo" }));
        set("nickname", "�Ϻ���");
        set("long",
"�͵�ŵ��İ��֣������⣬����Ц���еģ�����\n"
"ͬ�������еڶ����ǻ�ɽ������һ����Ψһ����Ͷʦ�ġ�\n");
        set("gender", "����");
        set("age", 54);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 24);
        set("per", 18);
        set("int", 25);
        set("con", 20);
        set("dex", 20);

        set("max_qi", 3000);
        set("max_jing", 1800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("eff_jingli", 1800);

        set("jiali", 150);
        set("combat_exp", 3000000);
        set("score", 6000);
        set("miji",1);
        set_skill("force", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("sword", 350);
        set_skill("cuff", 250);
        set_skill("hand", 250);
        set_skill("songshan-jian", 250);
        set_skill("huashan-jianfa", 350);
        set_skill("huashan-shenfa", 250);
        set_skill("poyu-quan", 250);
        set_skill("hanbing-zhenqi", 250);
        set_skill("songyang-shou", 250);
       // set_skill("zhengqi-jue", 100);
        set_skill("huashan-qigong", 250);

        map_skill("hand", "songyang-shou");
        map_skill("dodge", "huashan-shenfa");
        map_skill("force", "huashan-qigong");
        map_skill("parry", "huashan-jianfa");
        map_skill("sword", "huashan-jianfa");
        map_skill("cuff", "poyu-quan");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("hand", "songyang-shou");
        set("chat_msg_combat", ({
               	(: perform_action, "sword.fengyi" :),
				(: exert_function, "juli" :),
        }) );
        set("chat_chance", 100);
        set("chat_msg", ({
                
        }) );
        set("inquiry", ([
                "��ϼ�ؼ�" : (: ask_me :),
                 "������" : (: ask_gold :),
        ]) );

        create_family("��ɽ��", 14, "����");

        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}
/*void reset()
{
	object obb;
	if (clonep() && (obb = unew(__DIR__"obj/zixia")))
		obb->move(this_object());
} */

string ask_me(object who)
{
       int i;
        object *ob;
		object book,me;
        me=this_player();
		//if (!me->query_temp("zixia_asklao")) return "����ϼ�ؼ������һ�ɽ��һ�似��";
		if ( present("zixia miji", me))
		     return "�ף�����ϼ�ؼ���������������ô��������������";
		
	  
       
		book = new(BOOK_D("zixia"));
		book->move(this_object());
        if (me->query("quest/zixia/pass"))
		{
			message_vision(HIC"�͵�ŵ��$N����һ�����ۣ����һ����֪�������Լ��ĵ�ϸ������$Nһ����ϼ�ؼ����ת����ȥ��\n"NOR,me);
			
			book->move(me);
			return "�͵�ŵ��������ǰ���͵�ŵ�ˣ�����������װ���������µ����ӣ����������ǽ���,�ƺ�����ʲô������һ����\n";
		}
		if( (time()- me->query("quest/zixia/time"))<86400)		
     		return "������Ҳ̫�ڿ���Ү������ȥ��Ϣһ�°ɡ�\n";
	    if( is_fighting() || !me->query_temp("quest/huashan/zixia5") )
            return "�Բ�������£��Ҳ�������㻹������ʦ��ȥ�ɣ�\n";
       	me->delete_temp("quest/huashan/zixia5");
		me->set_temp("zixia_asklao",1);
		
		set_temp("apply/attack",  150);
        set_temp("apply/defense", 150);
		set_temp("apply/armor",   150);
        set_temp("apply/damage",  150);
		set_temp("apply/sword",   150);
		
        message("vision",
                YEL "����������㶼֪���ˣ�������ȥ���ɣ�\n"
                "�͵�ŵʹ���������������棬�����ޱȣ�һ������Ц�����ģ����\n" NOR,
                environment(), this_object() );
        
       ob = all_inventory(environment(this_object()));
	   for(i=sizeof(ob)-1; i>=0; i--) {
                if( !userp(ob[i]) ) continue;
                /*if( ob[i]->query_temp("quest/huashan/zixia5"))
                        {
                         ob[i]->delete_temp("hs/askzixia");
						// book = unew(__DIR__"obj/zixia");
						
                         if( clonep(book)){
							 book->move(this_object());
							 write("eeeeeeeee");}
						}*/
              
			   kill_ob(ob[i]);
               ob[i]->fight(this_object());
        }
                            
        return "\n�Ҵ���Ͷʦ�����踺�أ��㾹�Ҵ��ҵ����⣬ȥ���ɣ�\n";
}

void die()
{
        
		int i,j;
		object me = query_temp("last_damage_from");
		//object me = this_player();
	    object ob = present("zixia miji", this_object());
		
		if (objectp(me))
		{	
		
	    //if (!me->query_temp("zixia_asklao")) return "����ϼ�ؼ������һ�ɽ��һ�似��";
     	j = 25;
		if(me->query("m-card-vip")) j =  22;
		if(me->query("y-card-vip")) j =  18;
		if(me->query("buyvip"))     j =  15;
		j=random(j);
		i=random(me->query("kar"));
		if ( ob ) {		
		    if (objectp(me)
				&& me->query_temp("zixia_asklao")
				&& me->query("kar")<31
				&& i > 28
				&& random(me->query("con"))>40
				&& j<3)      
              {
			     command("say ����������Ҳ������Ե֮�ˣ��Ȿ����ϼ�ؼ����ͽ�����ɡ�");
				 message_vision(HIC"\n ��ϲ������ɽ�Ź�����ϼ��һ��������������������ڵó���Ը��\n", me);
			
			     me->set("quest/zixia/pass", 1);
			     me->delete_temp("zixia_asklao");
				 log_file("quest/zixia", sprintf("%s(%s) ʧ��%d�κ�����ǧ��������ڳɹ��⿪��ϼ������Դ��%d�����飺%d��\n", me->name(1),me->query("id"), me->query("quest/zixia/fail"),me->query("kar"),me->query("combat_exp")) );
				 me->set("title",HIM"��ϼ������"NOR);
			     ob->set("owner", me);
			     ob->move(me);
	        }
            else {
			     message_vision(CYN"\n$Nŭ�е�������ʹ�����ˣ����Ҳ����õ�����ϼ�ؼ�������������������\n"NOR, this_object());
			     message_vision("$N���ǡ���ϼ�ؼ�������˫����һ�꣬����������һ��ԭ��ʮ�ֳ¾ɵĲ�ҳ��ʱ������Ƭ��\n\n", this_object());
			     log_file("quest/zixia", sprintf("%s(%s) ������ϼ��ʧ��%d�Ρ���Դ��%d�����飺%d��\n", me->name(1),me->query("id"), me->query("quest/zixia/fail"),me->query("kar"),me->query("combat_exp")) );
				 if ( objectp(me)) {
				    me->add("quest/zixia/fail", 1);
				    me->set("quest/zixia/time", time());
					}
			     ob->set("name", HIW"��ϼ�ؼ�����Ƭ"NOR);
			     ob->move(environment(this_object()));
				 me->delete_temp("zixia_asklao");
               }
			me->delete_temp("zixia_asklao");
		}
		}
	::die();
}
int ask_gold(object who)
{
        object me = this_player();
        

        if( me->query("family/family_name") != "��ɽ��" ) {
                command("hmm "+(string)me->query("id"));
                command("say ������ɵ��ӣ�Ҳ�������ĳ�����\n");
                return 1;
        }

        if( me->query("shen") < 10000 ) {
                command("noway "+(string)me->query("id"));
                command("say ��Ŀ¶�׹�,����Ǯ���²�������������\n");
                return 1;
        }
        if( (int)me->query("huashan_given") <(int)me->query("age")){
                 command("nod "+(string)me->query("id"));
               who->add_money("gold",(int)(me->query_skill("huashan-jianfa", 1)/2) );
               command("give "+me->query("id")+" "+(int)(me->query_skill("huashan-jianfa", 1))/2+" gold");
                me->set("huashan_given",(int)me->query("age"));

                command("say ����" + RANK_D->query_respect(me) + "���ҵ�����Ѿ�������֪�ˣ�����������һ�������˲ţ�");
		command("say ��������ЩС��˼������" + RANK_D->query_respect(me) + "���ұ������ܰ���");
        } else command("say " + RANK_D->query_respect(me) + "����õ������ŵ���ʶ���ڽ������滹����Ŭ������");

        return 1;
}