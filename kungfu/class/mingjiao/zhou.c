// zhou.c 周颠
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
        set_name("周颠", ({ "zhou dian","zhou","dian" }) );
        set("title", "明教五散人");
        
        set("gender", "男性");
        set("age",52);
        set("long", "他就是明教五散人之一的周颠。\n");
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

        create_family("明教",36,"散人");

        set("max_qi",15000);
        set("max_jing",5200);
        set("jiali",200);
        set("eff_jingli",5200);
        set("inquiry", ([
                "借刀"     : (: ask_blade :),
			     "焚我残躯"     : (: ask_canqu :),

                "青焰刀" : "那是我的随身兵器，想用，可以借给你。\n",
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
        return RANK_D->query_respect(me)+"的功夫太差，借给你，怕你也保不住宝刀。";
        if ( present("qingyan dao", me)|| me->query_temp("qydao"))
                return RANK_D->query_respect(this_player()) + 
                "刀只有一把，已经借给你啦！";
        if ( blade=present("qingyan dao", ob))
        command("give qingyan dao to "+me->query("id"));
        if(!objectp(blade))   blade = unew(BINGQI_D("blade/qingyan-dao"));
        if(!objectp(blade))   return "抱歉，这把青焰刀我已经借给别人了。"; 

        blade->move(me);
        blade = unew(BINGQI_D("blade"));
        blade->move(this_object());
        me->set_temp("qydao",1);
        command("wield dao"); 
        return "大家都是江湖同道，交个朋友,尽管拿去用。";
         
}
string ask_canqu()
{ 
        object me,ob;
		int i,j;
        me = this_player(); 
        ob = this_object();

        if ( me->query("family/family_name")!="明教" )
        return RANK_D->query_respect(me)+"不是明教弟子，岂能偷学明教武功。\n";
        
		if (me->query_skill("lieyan-dao",1)<200)
                return RANK_D->query_respect(this_player()) + 
                "你的烈焰刀等级不足200，还不赶紧修炼去！";
        if (me->query("quest/mj/lyd/canqu/pass"))
        {
			return "你已经解开了“焚我残躯”这个刀法秘诀\n";
        }

       if (time()-me->query("quest/mj/lyd/canqu/time")<86400)
        {
			return "你来的太频繁了，不利于修行。\n";
        }
	   message_vision(HIY"$N看着$n，慢慢说道：“想当初我大明教合力营救谢狮王，在少林寺那一战\n"
					"可谓惊心动魄，幸好有教主力压群雄，否则后果不堪设想。每当我想起当初在伏魔圈\n"+
				   HIM"和少林三老那一战，如果不是当时我以刀划破面额，袭扰三老注意力，后果不好说。\n"NOR,this_object(),me);
	
 
		i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		command("say 后来我熟读本教教义，体味了一个道理，“熊熊烈火，焚我残躯”原来是背后隐藏一个道理。\n");
		command("say 只要你舍生忘死，不顾一切，敌人终究还是会胆寒的！\n");
		
		command("pat "+me->query("id"));
		command("laugh ");
	    message_vision(HIR"$N看着$n，慢慢说道：“你要想明白此中真意，要好好听我的口诀,跟我念！“\n"
					RED"熊熊烈火\n"+
					HIG"焚我残躯\n"+
					YEL"生亦何欢\n"
					MAG"死亦何苦\n"+
					BLU"为善除恶\n"
					WHT"惟光明故\n"
					CYN"喜乐悲愁\n"
					HIY"皆归尘土\n"
					HIW"怜我世人\n"
					HIG"忧患实多\n"
					HIM"怜我世人\n"
					HIR"忧患实多\n"
				    HIC"...........。\n"NOR,this_object(),me);
		message_vision(HIR"\n\n周颠越说声音越是宏大高亢，其身上的气势却无形中增加不少！\n"NOR,me);
		if( i<5
			&& me->query("kar")<31
			&& j >= 24 ) 
		{
			tell_object(me,HIY"\n你听了周颠的亲自指点，联想起早期自己所用烈焰刀的种种心得，两下印照。\n"NOR);
			tell_object(me,HIG"\n心中忽有所悟，下意识间你拿起刀来，在自己脸上划了几下，随即也随着周颠诵了起来。\n"
								RED"熊熊烈火\n"+
					HIG"焚我残躯\n"+
					YEL"生亦何欢\n"
					MAG"死亦何苦\n"+
					BLU"为善除恶\n"
					WHT"惟光明故\n"
					CYN"喜乐悲愁\n"
					HIY"皆归尘土\n"
					HIW"怜我世人\n"
					HIG"忧患实多\n"
					HIM"怜我世人\n"
					HIR"忧患实多\n"

							 HBYEL+"恭喜你！经过千辛万苦终于领悟了这门焚我残躯绝技的运用法门。心中大喜。\n"NOR);
			me->set("quest/mj/lyd/canqu/pass",1);
			log_file("quest/lydcanqu", sprintf("%8s(%8s) 失败%d次后，学到烈焰刀焚我残躯绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/mj/lyd/canqu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			command("haha"+me->query("id"));		
			
			return "恭喜解密昆仑烈焰刀焚我残躯绝技成功!\n";
			
		}	
	   else
		{
			log_file("quest/lydcanqu", sprintf("%8s(%8s) 解密烈焰刀焚我残躯绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/mj/lyd/canqu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"你听了周颠的指点，可是对烈焰刀焚我残躯的奥妙全然不得要领。\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/mj/lyd/canqu/fail",1);
			me->set("quest/mj/lyd/canqu/time",time());
			me->start_busy(1+random(3));
			
			return "非常遗憾解密昆仑烈焰刀焚我残躯失败"+me->query("quest/mj/lyd/canqu/fail")+"次。\n";
		}
				
		
		return "哈哈...\n";
         
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

        
        if (userp(ob) && ob->query("family/family_name") == "明教") {
                if (me->query("family/family_name") == "明教") { 
        message_vision(ob2->name()+"对$N喝道：身为明教弟子，竟然杀自己的同门？我宰了你！\n", me);
                }
                else {
                        message_vision(ob2->name()+"对$N喝道：大胆狂徒，居然敢来明教撒野！\n", me);
                        kill_ob(me);
                }
                me->set("vendetta/明教", 1);
                return 1;
        }
        return 0;
}


#include "5san_app.h";

