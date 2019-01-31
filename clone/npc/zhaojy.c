// zhaojy.c 老爵爷
#include "ansi.h"
inherit NPC;

void consider();

string ask_bdjmm();


void create()
{
	set_name("赵爵爷", ({ "zhao jueye","zhao","jueye" }) );
	set("gender", "男性" );
	set("age", 67);
	set("long", "满头银发，但面色红润宛如壮年，双目炯炯有神。\n");
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
		"赵爵爷深深叹了口气，“我太祖威名盖世，靠的就是一手大洪拳打遍天下无对手...”\n",
		"赵爵爷簇了簇眉，似乎想再说些什么。\n",
		(: random_move :)
	}) );
	
	set("inquiry", ([		
		"八段锦的秘密":(: ask_bdjmm :),		
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
		return "你已经知道了还来问我？\n";
	
	if( me->is_busy() || me->is_fighting() ) return "你正忙着呢。\n";

	if( ob->is_busy() || ob->is_fighting() ) return ob->name()+"正忙着呢。\n";	

    time = time() - me->query("quest/baduanjin/time");
	if(me->query("quest/baduanjin/time") && time < 86400)
		return "嗯？你不是刚来请教过我吗？还是再努力段时间吧！";  
	
	if (me->query_temp("baduanjian/quest",1))
	{
		me->start_busy(1);
		message_vision(CYN"$N对着$n说道：“请前辈指点"+RANK_D->query_self(me)+"八段锦的精义！”\n"NOR, me, ob);	
	    
		message_vision(CYN"$N对着$n说道：“既然你已经得到我大宋皇室八段锦之传承，那么看好了...”\n"NOR, ob, me);
	    COMBAT_D->do_attack(ob, me, 0, 1);	
	    COMBAT_D->do_attack(ob, me, 0,1);	
	    COMBAT_D->do_attack(ob, me,0, 1);
	
	    message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	    message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	    message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
		
		if( random(me->query("kar")) > 28 && random(30)==3) {	// 随机福源
			message_vision(HIW"$N突然捕捉住交手瞬间的一幕，渐渐领悟出八段锦的使用法门。\n", me);
			tell_object(me, BYEL"恭喜你，你于" + NATURE_D->game_time() + "领悟了八段锦的使用法门。\n"NOR);
			me->set("quest/baduanjin/pass2", 1);
			me->set("quest/baduanjin/time",time());
			me->set("title",HIY"百姓王"NOR);
			me->set("mytitle/quest/bdjtitle",HIY"百姓王"NOR);
			log_file("quest/baduanjin",sprintf("%-18s失败多次后，从赵爵爷处学到八段锦真意，福：%d。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",me->query("kar")), me);
			return "恭喜，恭喜。";
		}
		else {
			message_vision(HIC"$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n", me);
			me->set("quest/baduanjin/time",time());
			return "你太没有用，退下吧。";
		}		
	}
	else return "我不知道你在说什么。";
}




