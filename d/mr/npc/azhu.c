// By Spiderii 从新编译
inherit NPC;
#include <ansi.h>
int ask_yirong();
int ask_yirong2();
int ask_yirong3();
int ask_help();

void create()
{
        set_name("阿朱", ({ "a zhu", "a", "zhu" }));
        set("gender", "女性");
        set("age", 20);
        set("long","她是个二十多岁的少女，一对眸子有说不出的神采，\n"+
                   "面容清秀,虽然算不上美丽,但别有一番滋味在心头。\n");
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 26);
        set("per", 25);
        set("unique", 1);
        set("location", 1);
        set("combat_exp", 14000);
        set("shen_type", 0);
        set("attitude", "peaceful");
	 set("max_qi",1000);
        set("max_jing",1000);
        set("neili",1000);
        set("max_neili",1000);
	 set("jiali",30);
	 set("score", 8000);
        set_skill("cuff", 50);
	 set_skill("parry",50);
	 set_skill("yanling-shenfa",50);
        set_skill("dodge", 50);
	 set_skill("force",50);
	 set_skill("shenyuan-gong",50);

	 map_skill("force","shenyuan-gong");
	 map_skill("dodge","yanling-shenfa");      
         
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);


        set("inquiry", ([           
                     "高深" : (: ask_yirong2 :),
                     "心愿" : (: ask_help :),
                     "易容术" : (: ask_yirong :),
                     "人皮面具"  : (: ask_yirong3 :),

        ]));
        setup();
        carry_object(__DIR__"obj/shoe")->wear();
        carry_object(__DIR__"obj/red_silk")->wear();
        carry_object(__DIR__"obj/skirt")->wear();

}

int ask_yirong()
{          
       object me = this_player();
        string msg;
        msg = HIY"阿朱说道:一般所谓易容术，其实应该叫做变装术。\n"NOR;
        msg+= HIY"阿朱说道:是依靠假发，假须，不同的衣服，将一个人变成不同的另一个人。\n"NOR;
        msg+= HIY"阿朱说道:这种所谓易容术，简直就是小孩子的玩意，也是最低下的一种。\n"NOR;
        msg+= HIY"阿朱说道:与高深的易容术相比较起来,差距甚大。\n"NOR;
        message_vision(msg, me);
        me->set_temp("azhu/yirong1",1);
        return 1;
}

int ask_yirong2()
{ 
        object me = this_player();
        string msg;
        if (me->query_temp("azhu/yirong1")==1)
        {
        msg = HIY"阿朱说道:高深一些的易容术,要求繁多,非一朝一夕即可学得。\n"NOR;
        msg+= HIY"阿朱说道:人所以相貌不同，可以说完全是因为骨肉的各异不同所造成。\n"NOR;
        msg+= HIY"阿朱说道:高明的易容术通常需要如缩骨功,变声术这类技巧武功加以辅助,方可达到令人满意的效果。\n"NOR;
        msg+= HIY"阿朱说道:想当初我只凭一张人皮面具,即可在众目睽睽之下,入那少林寺窃得镇寺之宝--易筋经!\n"NOR;
        msg+= HIY"阿朱说道:可见我慕容世家除 以彼之道,还施彼身 之外,易容术亦可谓独步武林!\n"NOR;
        message_vision(msg, me);
        me->set_temp("azhu/yirong2",1);
        return 1;
}
 message_vision(HIC"阿朱奇怪的问道：“你打听这些做什么？”\n"NOR, me);
        return 1;


}
int ask_yirong3()
{ 
        object me = this_player();
        string msg;
        if (me->query_temp("azhu/yirong2")==1)
        {
        msg = HIY"阿朱说道:此人皮面具乃是经我慕容世家精心研制而成。\n"NOR;
        msg+= HIY"阿朱说道:放眼江湖,能识破其中奥妙的不过寥寥数人而已。\n"NOR;
        msg+= HIY"阿朱说道:若阁下能帮我完成一桩心愿,我愿将此面具双手奉上。\n"NOR;
        msg+= HIY"阿朱说道:他日行走江湖,也可为阁下省却诸多烦恼,不知意下如何?\n"NOR;
        message_vision(msg, me);
        me->set_temp("azhu/yirong3",1);
        return 1;
}
 message_vision(HIC"阿朱奇怪的问道：“你打听这些做什么？”\n"NOR, me);
        return 1;


}


int ask_help()
{        
        object baofu;
        object me = this_player();
        string msg;
        if (me->query_temp("azhu/yirong3")==1)
        {
        msg = HIY"阿朱说道:当日我为报我家公子知遇之恩,私闯嵩山少林,盗得其镇寺之宝--易筋经,惹的天下大乱。\n"NOR;
        msg+= HIY"阿朱说道:现下细细回想,深悔当日之卤莽,心下懊悔非常。\n"NOR;
        msg+= HIY"阿朱说道:此番别无它求,只想请阁下代我还经少林，以了我此桩心愿。\n"NOR;
        msg+= HIY"阿朱将一个布包交给了你!\n"NOR;
        message_vision(msg, me);
        baofu=new("/d/mr/npc/obj/baofu");
	    baofu->move(this_player());
        me->set_temp("azhu/mask",1);
        return 1;
}
 message_vision(HIC"阿朱奇怪的问道：“你打听这些做什么？”\n"NOR, me);
        return 1;


}

int accept_object(object me, object obj)
{
        object mask;
        if ((string)obj->query("id")=="xuanci letter") {
        message("vision",me->name()+"给阿朱一封少林寺玄慈方丈的亲笔书信。\n",environment(me),
            ({me}));
        mask = unew("/d/mr/npc/obj/mask");
		
        if (me->query_temp("azhu/mask3") < 1) return notify_fail (CYN"阿朱说道：你给我这个做什么?\n"NOR); 
        if(!clonep(mask))
                return notify_fail(HIR"你来晚了，人皮面具已经给人取走了。\n"NOR);
        if(clonep(mask) && mask->violate_unique()){
                destruct(mask);
                return notify_fail(HIR"你来晚了，人皮面具已经给人取走了。\n"NOR);
        }
        command("thank "+me->query("id"));
        command("say 多谢"+RANK_D->query_respect(me)+"帮小女子了却这桩心愿。");
        mask->move(me);   
		me->set_temp("yjj/givemask",1);
        message_vision("$n递给$N一张人皮面具。\n", me, this_object() );
        CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "机缘巧合之下,得到一张" + HIW + "人皮面具" + NOR + "。\n");          
        command("say 这面具请你收好,望你勿要以此为恶。");
        remove_call_out("destroying");
		
        call_out("destroying", 1, this_object(), obj);
        return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}
