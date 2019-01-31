// NPC: /d/meizhuang/npc/huang.c
// By action@SJ 2009/1/11

#include <ansi.h>
inherit NPC;
string ask_wuxian();
void create()
{
	object ob;

	set_name("黄钟公", ({ "huangzhong gong", "huang", "gong" }));
	set("nickname", HIR"梅庄大庄主"NOR);

	set("gender", "男性");
	set("age", 65);
	set("no_quest", 1);
	set("no_bark", 1);
	set("long",
      "他就是梅庄四位庄主排行第一的黄钟公。\n"
      "身穿一件干干净净的黄色长袍。\n"
      "他已年愈六旬，身材中等，面容和蔼可亲。\n");
	set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 4000);
	set("max_jing", 4000);
	set("jingli", 4000);
	set("max_jingli", 4000);
	set("max_neili", 5000);
	set("neili", 8000);
	set("combat_exp", 3200000);
	set("attitude", "peaceful");

	set_skill("art", 180);
	set_skill("medicine", 120);
	set_skill("literate", 160);
	set_skill("force", 450);
	set_skill("parry", 450);
	set_skill("huanmo-wubu", 450);
	set_skill("sword", 450);
	set_skill("tianmo-gong", 450);
	set_skill("qixian-wuxingjian", 450);
	set_skill("strike", 450);
	set_skill("tianmo-zhang", 450);

	map_skill("force", "tianmo-gong");
	map_skill("dodge", "huanmo-wubu");
	map_skill("sword", "qixian-wuxingjian");
	map_skill("parry", "qixian-wuxingjian");
	map_skill("strike", "tianmo-zhang");
	set("inquiry", ([
         
		 "五弦音律" : (: ask_wuxian :),
        ]));
	set("chat_chance", 1);
	set("chat_msg", ({
		"黄钟公叹了口气道：谁能将“广陵散”弄来给我呀……”\n",
	}));

	set_temp("apply/damage", 260);

	setup();
        if (clonep()) {
                ob = unew(BINGQI_D("sword/yaoqin"));
                if (!ob) ob = unew(BINGQI_D("yuxiao2"));
                ob->move(this_object());
                ob->wield();
                carry_object(ARMOR_D("cloth"))->wear();
        }
}

int accept_object(object who, object ob)
{
        object me;
       // mapping fam;
        me = this_object();

       if (!who->query("family") || who->query("family/family_name") !="日月神教"){
             command("thank "+ (string)who->query("id"));
             command("say 你与本派素无来往，不知为何送如此厚礼？\n");
             return 0;
        }
       /* 
		if (!this_player()->query_temp("mz_entrance")){
             command("say 你是怎么进来的？");
             return 0;
        }*/
        
       // if (fam["generation"] == 3)
        if ((string)ob->query("id") == "guangling san"&& who->query_temp("mz_entrance")){
            command("haha "+(string)who->query("id"));
            call_out("destroying", 1, ob);
            command("say 你帮我办成了这件事，我很高兴，你去找我的二弟黑白子试试吧，或许他能给你一些提示！");
            who->set_temp("meizhuangguangling",1);
			
            who->delete_temp("mz_entrance");
            return 1;
            }
         else if ((string)ob->query("id") == "guangling san")
         {
			 command("你送如此大礼给我，甚是汗颜，我无以为报，只能将我多年的心得传授给你。\n");
			 who->set_temp("glsgived",1);
			 destruct(ob);
			 return 1;
         }
        command("? "+ (string)who->query("id"));
        return 0;
}

void destroying(object obj)
{
        if(! obj) return;
        destruct(obj);
}

string ask_wuxian()
{
    int i,j;
	object me=this_player();
    if (me->query("family/family_name")!="日月神教")
       return "你不是我神教弟子，鬼鬼祟祟来此作甚？\n";
	if (!me->query_temp("glsgived"))
	   return "广陵散乃绝世好曲，当真是余音绕连三日不绝。\n";
	if (!me->query_skill("qixian-wuxingjian")) return "你都不会七弦无形剑。\n";
	
	if (me->query("quest/hmy/qxwxj/wuxian/pass"))
	   return "你已经彻底了解七弦无形剑五弦乐音！\n";
    if (time()-me->query("quest/hmy/qxwxj/wuxian/time")<86400)
       return "你来的也太勤快点了！\n";
    
	command("smile "+me->query("id"));
	command("say 既然您将那本琴谱相赠，我焉能对您隐瞒，不过能否解密的了，还要看您的悟性了。\n");
	command("say 所谓的五弦音律是指，宫、商、角、徵、羽，若功力高深后，可以将内力融入琴音。\n");
	command("say 这门功夫叫做无形剑，专伤人内力，最是厉害无比。\n ");
	
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	if (me->query("kar")<31
		&& random(me->query("kar"))>=22
		&& me->query("int")>=25
		&& i<6)
	    {
          message_vision(HIY"$N听着黄钟公的讲解，不但将手按在瑶琴山，一遍演练，一遍体悟。\n"+
						"忽然间，内力涌动，瞬间走通数个穴位，劲气通过琴弦陡然而发！\n"NOR,me);
	      message_vision(HIC"$N恭喜你，你领悟黄钟公的无形剑以乐音伤人的绝技。\n"NOR,me);
	  
	   log_file("quest/qxwxjwuxian",sprintf("%s(%s) 从黄钟公处，无意中领悟五弦音律，以音伤敌的绝技。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,me->query("quest/hmy/qxwxj/wuxian/fail"),me->query("combat_exp"),me));
	   
	   me->set("quest/hmy/qxwxj/wuxian/pass",1);
	   me->improve_skill("qixian-wuxingjian",20);
       message_vision(HIC"你的七弦无形剑进步了！\n"NOR,me);
	   me->delete_temp("glsgived");
	   me->start_busy(1);
	   return "";
	  }
	   else {
		message_vision(HIY"\n 乐音伤敌乃是需要极高的内力和悟性，本次领悟失败，下次再来。\n"NOR,me);
	    log_file("quest/qxwxjwuxian",sprintf("%s(%s) 领悟七弦无形剑五弦乐音的绝技失败。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,me->query("quest/hmy/qxwxj/wuxian/fail"),me->query("combat_exp"),me));
		me->add("quest/hmy/qxwxj/wuxian/fail",1);
		me->set("quest/hmy/qxwxj/wuxian/time",time());
		me->delete_temp("glsgived");
		me->start_busy(1);
        return "";
	   }
	// return "五弦即是发五音,五音齐发，群雄束手。\n";
}
