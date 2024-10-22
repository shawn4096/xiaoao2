//五彩喇叭
#include <ansi.h>
inherit SPEC;

void create()
{
	set_name(HIM"五彩喇叭" NOR, ({ "wucai laba","laba","wucai"}));
        set("long", 
                 "一个五彩喇叭，用它说话可以带颜色哦。\n"
                 "用法：\n"
                 "cui 动作 你的词语 动作可以是say reply shout chat 等 \n"
                 "比如 cui chat $HIG$ hi\n"
                 "颜色列表：\n"
                        "                     $NOR$ - 恢复正常颜色\n"
			"$RED$ - "RED"红色"NOR"         $HIR$ - "HIR"亮红色\n"NOR
			"$GRN$ - "GRN"绿色"NOR"         $HIG$ - "HIG"亮绿色\n"NOR
			"$YEL$ - "YEL"土黄色"NOR"       $HIY$ - "HIY"黄色\n"NOR
			"$BLU$ - "BLU"深蓝色"NOR"       $HIB$ - "HIB"蓝色\n"NOR
			"$MAG$ - "MAG"浅紫色"NOR"       $HIM$ - "HIM"粉红色\n"NOR
			"$CYN$ - "CYN"蓝绿色"NOR"       $HIC$ - "HIC"天青色\n"NOR
			"$WHT$ - 浅灰色       $HIW$ - "HIW"白色\n"NOR
                        );
	set("unit","个");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
	set("degree",20);
	set("flag","spec/laba");
	set("desc","用它说话可以带颜色。");
	set("credit",100);	
        setup();
}

void init()
{
        add_action("do_cui", "cui");
        add_action("do_cui", "chui");
}

int do_cui(string arg)
{
        string arg1,arg2;
        object me = this_player(); 
        if (!arg) return notify_fail("你要吹什么？\n");
        sscanf(arg,"%s %s",arg1,arg2);
        if (arg1 != "chat" && arg1 != "sj" && arg1 !="party" && arg1 != "group" 
        && arg1 !="say" && arg1 !="tell" && arg1 !="reply" && arg1 !="whisper" && arg1 !="shout")
        return notify_fail("你想用五彩喇叭吹什么？\n");
        arg2 = replace_string(arg2, "$RED$", RED);
        arg2 = replace_string(arg2, "$GRN$", GRN);
        arg2 = replace_string(arg2, "$YEL$", YEL);
        arg2 = replace_string(arg2, "$BLU$", BLU);
        arg2 = replace_string(arg2, "$MAG$", MAG);
        arg2 = replace_string(arg2, "$CYN$", CYN);
        arg2 = replace_string(arg2, "$WHT$", WHT);
        arg2 = replace_string(arg2, "$HIR$", HIR);
        arg2 = replace_string(arg2, "$HIG$", HIG);
        arg2 = replace_string(arg2, "$HIY$", HIY);
        arg2 = replace_string(arg2, "$HIB$", HIB);
        arg2 = replace_string(arg2, "$HIM$", HIM);
        arg2 = replace_string(arg2, "$HIC$", HIC);
        arg2 = replace_string(arg2, "$HIW$", HIW);
        arg2 = replace_string(arg2, "$NOR$", NOR);
        arg2 = replace_string(arg2, "$BRED$", BRED);
        arg2 = replace_string(arg2, "$BGRN$", BGRN);
        arg2 = replace_string(arg2, "$BBLU$", BBLU);
        arg2 = replace_string(arg2, "$BYEL$", BYEL);
        arg2 = replace_string(arg2, "$BMAG$", BMAG);
        arg2 = replace_string(arg2, "$BCYN$", BCYN);
        arg2 = replace_string(arg2, "$BBLK$", BBLK);
        arg2 = replace_string(arg2, "$HBRED$", HBRED);
        arg2 = replace_string(arg2, "$HBGRN$", HBGRN);
        arg2 = replace_string(arg2, "$HBBLU$", HBBLU);
        arg2 = replace_string(arg2, "$HBYEL$", HBYEL);
        arg2 = replace_string(arg2, "$HBMAG$", HBMAG);
        arg2 = replace_string(arg2, "$HBCYN$", HBCYN);
        arg2 = replace_string(arg2, "$HBWHT$", HBWHT);
        //arg2 = replace_string(arg2, "$BLINK$", BLINK);
        arg2 += NOR;
       	me->force_me(arg1+" "+arg2);
	degree();
	return 1;
}