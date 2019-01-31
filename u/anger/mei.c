// mei.c 梅超风
// Modified by Darken/Numa@SJ for taohua quest
//增加九阴白骨爪后阶提升 by renlai
#include <ansi.h>
inherit NPC;
string jybgz();
void create()
{
	set_name( "梅超风" ,({ "mei chaofeng", "mei" }));
	set("title", "黑风双煞");
	set("nickname", HIB"铁尸"NOR);
	set("gender", "女性");
	set("age", 32);
	set("long",
		"梅超风是黄药师唯一的女弟子，本来极受黄药师疼爱，可惜她与师兄陈玄风\n"
		"暗生情愫，他们偷了《九阴真经下卷》私奔。\n"
		"她面色大概因为久居海岛显得黝黑，模样却颇为俏丽。她在桃花弟子中尤精通鞭法。\n");
	set("attitude", "aggressive");

        set("str", 47);
        set("int", 32);
        set("con", 35);
        set("unique", 1);

        set("no_get", "梅超风对你而言太重了。\n");
        set("max_qi",33500);
        set("qi",33500);
        set("max_jing",3000);
        set("neili", 24500);
        set("max_neili", 24500);
        set("jiali", 100);
        set("shen",-50000);

        set("combat_exp", 9400000);

        set_skill("claw", 450);
        set_skill("force", 450);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("leg", 450);
        set_skill("jiuyin-baiguzhua", 450);
        set_skill("bihai-chaosheng", 450);
        set_skill("suibo-zhuliu", 450);
        set_skill("xuanfeng-tui", 450);

        map_skill("force", "bihai-chaosheng");
        map_skill("parry", "jiuyin-baiguzhua");
        map_skill("dodge", "suibo-zhuliu");
        map_skill("claw", "jiuyin-baiguzhua");
        map_skill("leg", "xuanfeng-tui");
        prepare_skill("claw", "jiuyin-baiguzhua");

        create_family("桃花岛", 2, "被逐弟子");
        set("inquiry", ([
		"九阴白骨爪": (: jybgz :),
		"铁尸":     "江湖上的人都这么叫我的，你怕不怕？哈哈哈哈。",
		"东邪":     "那是我师父的绰号。",
		"西毒":     "那是与家师齐名的高手之一，是个老毒物，住在白驼山。",
		"南帝":     "段王爷已出家当和尚去了，法名叫一灯。",
		"北丐":     "北丐统领中原的丐帮，势力颇为强大。",
		"洪七公":   "洪七公武功高强，而且教会郭靖那小儿降龙十八掌，可恨！",
		"黄蓉":     "她是我师父的独女，最是刁蛮任性。",
		"郭靖":     "哼，就是这个小子暗算了我师哥，我绝不会放过他！",
		"杨康":     "康儿是我的徒弟，你见过他么？",
		"梅超风":   "不就是我么？你是白痴啊？",
		"陈玄风":   "他是我的师哥，也是我的夫君，可惜被郭靖那小儿暗算了。",
		"黄药师":   "他是我师父。",
		
	]) );
        setup();
}


string jybgz()
{
	object me = this_player();
	object ob = this_object();
	object kulou;
	int exp, time, night;
	mixed *local;
	night = 0;
	local = localtime(time() * 60);
	if (local[2] < 5 || local[2] >= 19) night = 1;	
	
	if ( me->query("shen") > 0) return "你不够心狠手辣，如何学会九阴白骨爪的真谛。\n";
	
	if( me->is_busy() || me->is_fighting() ) return "你正忙着呢。\n";

	if( ob->is_busy() || ob->is_fighting() ) return ob->name()+"正忙着呢。\n";	
  
    if (!night) return "练习九阴白骨爪必须夜深人静时分，现在我如何教你九阴白骨爪的真谛。\n";
    
	if( me->query("quest/jiuyin2/jybgz/pass") )
		return RANK_D->query_respect(me) + "，你已经学会九阴白骨爪真谛，又何故开此玩笑呢？";

    if( me->query_skill("jiuyin-baiguzhua", 1) < 350 )
		return RANK_D->query_respect(me) + "，你的九阴白骨爪造诣不够，还无法领悟我的精要所在！";
 
	time = time() - me->query("quest/jiuyin2/jybgz/time");
	if( me->query("quest/jiuyin2/jybgz/time") && time < 86400)
		return "嗯？你不是刚来请教过我吗？还是再努力段时间吧！";
	
	if( !kulou = present("kulou tou", me) ) {
		
		message_vision(CYN"$N对$n说：“请前辈指点晚辈"+RANK_D->query_self(me)+"九阴白骨爪的真谛！”\n"NOR, me, ob);
		message_vision(CYN"$n说：“" + RANK_D->query_respect(me) + "你先帮我找来骷髅头吧！”\n"NOR, me, ob);
		me->start_busy(1);
		return "速速去拿。";
	} else {
		
		kulou->move(ob);
		me->start_busy(1);
		message_vision(CYN"$N对着$n 将骷髅头交给梅超风说道：“请前辈指点"+RANK_D->query_self(me)+"九阴白骨爪奥义！”\n"NOR, me, ob);
	
	message_vision(HIW"只见$n绕着$N缓缓行走，骨节中发出微微响声，她脚步逐渐加快，骨节的响声也越来越响，越来越密，犹如几面羯鼓同时击奏一般!"NOR, me, ob);
	COMBAT_D->do_attack(ob, me, 0, 1);
	message_vision(HIW"只见$n双掌不住的忽伸忽缩，每一伸缩，手臂关节中都是喀喇声响，长发随着身形转动，在脑后拖得笔直，尤其诡异可怖。"NOR, me, ob);
	COMBAT_D->do_attack(ob, me, 0,1);
	message_vision(HIW"突然间$n右掌一立，左掌拍的一声打在$N胸前,眼见$N往后便倒，$n已转到$N身后，一掌打在$N后心。\n只见$n身形挫动，风声虎虎，接着连发八掌，一掌快似一掌，一掌猛似一掌，$N始终发不出一声。\n"NOR, me, ob);
	COMBAT_D->do_attack(ob, me,0, 1);
	message_vision(HIW"待到第九掌发出，那$n忽然跃起，飞身半空，头下脚上，噗的一声，右手手指插入了$N脑门。\n"NOR, me, ob);
	
	message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
	
	if( random(me->query("kar")) > 28) {	// 随机福源
			message_vision(HIW"$N突然捕捉住交手瞬间的一幕，渐渐领悟出九阴白骨爪的真谛。\n", me);
			tell_object(me, BYEL"恭喜你，你于" + NATURE_D->game_time() + "领悟了九阴白骨爪的真谛。\n"NOR);
			me->set("quest/jiuyin2/jybgz/pass", 1);
			me->set("quest/jiuyin2/jybgz/time",time());
			return "恭喜，恭喜。";
		} else {
			message_vision(HIC"$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n", me);
			me->set("quest/jiuyin2/jybgz/time",time());
			return "你太没有用，退下吧。";
		}
		
	}
	
}




void die()
{
	object ob = this_object(),me,cor;

	if (!ob->query_temp("target")){
		call_out("do_die",1,ob);
		return;
	}
        
	me = query_temp("last_damage_from");

	if (me->query("id") != ob->query_temp("target")) {
		ob->revive(1);
		command("say 好，居然还有" + me->name(1) + "帮你，哼！");
		message_vision(HIY"梅超风见形势不好，转身逃了！\n"NOR, me);
		destruct(ob);
		return;
	}
	else {
		if (me->query_temp("thd/onquest") > 2
		&& me->query_temp("thd/onquest") < 4) {
			ob->revive(1);
			ob->reicarnate();
			message_vision(HIY"梅超风运起残存的内力，又跳起来狠狠的瞪着$N。\n"NOR, me);
			if (objectp(cor = present("corpse",environment(ob)))) {
				tell_room(environment(ob),"梅超风将陈玄风的尸体扶了起来背在背上。\n");
				call_out("do_dest",1,cor);
			}
			command("stare");
			command("say 哼，咱们走着瞧！");
			message_vision(HIY"梅超风抱起陈玄风的尸身，一晃眼就不见了。\n\n\n"NOR, me);
			if (me->query("thd/quest1") < 1 && random(me->query_kar()/10) > 0) {
				message_vision(HIW"$N长途奔走又和黑风双刹缠斗许久，身法进步了一些！\n"NOR,me);
				me->set("thd/quest1",1);
			}
			me->set_temp("thd/onquest",4);
		}
		else if (me->query_temp("thd/onquest") > 5
			&& me->query_temp("thd/onquest") < 7 ) {
			me->set_temp("thd/onquest",7); 
			message_vision(HIM"梅超风身上掉下一把用皮革包裹的匕首。\n"NOR,me);
			message_vision(HIM"$N将匕首和皮革收了起来。\n"NOR,me);
			new(resolve_path(0, __DIR__"../obj/skin"))->move(me);
			new(resolve_path(0, __DIR__"../obj/bishou"))->move(me);
			call_out("do_die",1,ob);
			return;
		}
		call_out("do_dest",1,ob);
		return;
	}
}

void do_die(object ob)
{
        :: die();
}

void do_dest(object ob)
{
        destruct(ob);
}
