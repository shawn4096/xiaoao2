// zhaojy.c �Ͼ�ү
#include "ansi.h"
inherit NPC;

void consider();

string ask_bdjmm();


void create()
{
	set_name("�Ծ�ү", ({ "zhao jueye","zhao","jueye" }) );
	set("gender", "����" );
	set("age", 67);
	set("long", "��ͷ����������ɫ��������׳�꣬˫Ŀ��������\n");
	set("attitude", "peaceful");
    set("str", 28);
	set("con", 21);
	set("int", 20);
	set("dex", 25);


	set("max_qi", 9500);
	set("max_jing", 5800);
	set("neili", 6800);
	set("max_neili", 6800);
	set("jiali", 200);
	set("shen", 8000);
	set("startroom","/d/city/beidajie3");


	set("combat_exp", 950000);

	set_skill("force", 240);
	set_skill("cuff", 250);
	set_skill("dodge", 240);
	set_skill("parry", 240);
	set_skill("baduan-jin", 240);
	set_skill("literate", 220);
	set_skill("taizu-quan", 250);
	set_skill("caoshang-fei", 240);
    map_skill("force", "baduan-jin");
	map_skill("dodge", "caoshang-fei");
    map_skill("cuff", "taizu-quan");
    map_skill("parry", "taizu-quan");
    prepare_skill("cuff", "taizu-quan");


	set("chat_chance", 10);
	set("chat_msg", ({
		"�Ծ�ү����̾�˿���������̫���������������ľ���һ�ִ��ȭ��������޶���...��\n",
		"�Ծ�ү���˴�ü���ƺ�����˵Щʲô��\n",
		(: random_move :)
	}) );
	
	set("inquiry", ([		
		"�˶ν�������":(: ask_bdjmm :),		
	]));

	setup();
        carry_object(ARMOR_D("changshan4"))->wear();
        carry_object(ARMOR_D("buxue"))->wear();
        carry_object(ARMOR_D("ryyaodai"))->wear();
	//add_money("silver",30+random(30));
}

string ask_bdjmm()
{
	
	object me = this_player();
	object ob = this_object();
	int time=0;
	
	if(me->query("quest/baduanjin/pass2"))
		return "���Ѿ�֪���˻������ң�\n";
	
	if( me->is_busy() || me->is_fighting() ) return "����æ���ء�\n";

	if( ob->is_busy() || ob->is_fighting() ) return ob->name()+"��æ���ء�\n";	

    time = time() - me->query("quest/baduanjin/time");
	if(me->query("quest/baduanjin/time") && time < 86400)
		return "�ţ��㲻�Ǹ�����̹����𣿻�����Ŭ����ʱ��ɣ�";  
	
	if (me->query_temp("baduanjian/quest",1))
	{
		me->start_busy(1);
		message_vision(CYN"$N����$n˵��������ǰ��ָ��"+RANK_D->query_self(me)+"�˶ν��ľ��壡��\n"NOR, me, ob);	
	    
		message_vision(CYN"$N����$n˵��������Ȼ���Ѿ��õ��Ҵ��λ��Ұ˶ν�֮���У���ô������...��\n"NOR, ob, me);
	    COMBAT_D->do_attack(ob, me, 0, 1);	
	    COMBAT_D->do_attack(ob, me, 0,1);	
	    COMBAT_D->do_attack(ob, me,0, 1);
	
	    message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	    message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
	    message_vision(HIY"\n$Nƴ���ػ����Ÿղŵ���������ʼ����˼����.........\n", me);
		
		if( random(me->query("kar")) > 28 && random(30)==3) {	// �����Դ
			message_vision(HIW"$NͻȻ��׽ס����˲���һĻ������������˶ν���ʹ�÷��š�\n", me);
			tell_object(me, BYEL"��ϲ�㣬����" + NATURE_D->game_time() + "�����˰˶ν���ʹ�÷��š�\n"NOR);
			me->set("quest/baduanjin/pass2", 1);
			me->set("quest/baduanjin/time",time());
			me->set("title",HIY"������"NOR);
			me->set("mytitle/quest/bdjtitle",HIY"������"NOR);
			log_file("quest/baduanjin",sprintf("%-18sʧ�ܶ�κ󣬴��Ծ�ү��ѧ���˶ν����⣬����%d��\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",me->query("kar")), me);
			return "��ϲ����ϲ��";
		}
		else {
			message_vision(HIC"$Nҡ��ҡͷ�������������Ǻ����ѵġ���˵�գ������̾�˿�����\n", me);
			me->set("quest/baduanjin/time",time());
			return "��̫û���ã����°ɡ�";
		}		
	}
	else return "�Ҳ�֪������˵ʲô��";
}




