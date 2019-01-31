// 18niou.c
// by KinGSo
// 故事-侠客行

inherit ITEM;
#include <ansi.h>
void create()
{
        set_name(YEL"十八泥偶"NOR, ({"shiba niou", "shiba", "niou", "shibaniou"}));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "套");
                set("long", "这是一套按照十八罗汉捏成的泥偶，据传这套泥偶上面记载着一门高深的佛家内功心法。\n");
                set("value", 8000);
                set("unique", 1);
                set("material", "paper");
                set("no_give", "这么珍贵的东西，你可不能随意丢弃！\n");
                set("no_drop", "这么珍贵的东西，你可不能随意丢弃！\n");
                set("no_get", "这样东西是那人的宝贝，连睡觉都要当枕头垫，你无法拿取！\n");
                set("treasure", 1);
        }
}

void init()
{
        add_action("do_yanjiu", "yanxi");
}

int do_yanjiu(string arg)
{
        object me = this_player();
        object where = environment(me);
        int lhlevel, neili_lost;

        if(!id(arg)) return 0;

        if(me->query("gender") =="无性")
                return notify_fail("你无根无性，阴阳不调，难以领会高深的罗汉伏魔功。\n");
                
        if(me->is_busy()) 
                return notify_fail("你现在正忙着呢。\n");
                
        if(query_temp("quest/摩天崖/luohan"))
                return notify_fail("你从哪里偷来的？可不能偷读哦！\n");
                
        if(me->is_fighting())
                return notify_fail("你无法在战斗中专心下来研读新知！\n");
        
        if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("你不散去神照经，怎么修炼罗汉伏魔功。\n");
    
        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("你不散去冷泉神功，怎么修炼罗汉伏魔功。\n");

        if((int)me->query_skill("kuihua-mogong", 1) >= 1 )
                return notify_fail("你不散去葵花魔功，怎么修炼罗汉伏魔功。\n");

       if((int)me->query_skill("kuihua-shengong", 1) >= 1 )
                return notify_fail("你不散去葵花神功，怎么修炼罗汉伏魔功。\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("你不散去九阳神功，怎么修炼罗汉伏魔功。\n");  
     
       if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("你不散去蛤蟆功，怎么修炼罗汉伏魔功。\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("你不散去太玄功，怎么修炼罗汉伏魔功。\n");       
                
        if(where->query("outdoors") != "摩天崖顶" )
              return notify_fail("你只能在摩天崖顶才能静下心来研究十八泥偶。\n");
                
        if(me->query("jing") < 25)
                return notify_fail("你现在过于疲倦，无法专心下来研读新知。\n");
                
        if(me->query_skill("force",1) < 100) 
                return notify_fail("你的内功基础没有打好，不能修练。\n");
                
       if ((int)me->query("int") < 33)
                return notify_fail("由于你的悟性不够，无法研究十八泥偶。\n");

       if ((int)me->query("con") < 20)
                return notify_fail("由于你的根骨不够，无法研究十八泥偶。\n");

        if(this_object()->query("clone_by_wizard")) 
                return notify_fail("你从哪里偷来的？可不能偷读哦！\n");

        lhlevel = me->query_skill("luohan-fumogong", 1);
        if (lhlevel < 30)
                neili_lost = lhlevel / 2;
        else if (lhlevel< 70)
                neili_lost = lhlevel * 2 / 3;
        else if (lhlevel< 140)
                neili_lost = lhlevel * 3 / 4;
        else
                neili_lost = lhlevel ;
        if( neili_lost > 150) neili_lost = 150;
        if ( lhlevel >= (me->query_skill("force", 1) + 30))
                return notify_fail("由于你的内功的火侯不够，不能再获得更高一层的提高。\n");
        
        if (me->query("neili") < neili_lost) 
                return notify_fail("你内力不够，无法钻研这么高深的武功。\n");
        if (me->query("combat_exp") < lhlevel * lhlevel * lhlevel / 10) 
                return notify_fail("你的实战经验不足，再怎么读也没用。\n");
        if (lhlevel >= 221 && me->query("neili") < lhlevel * 3 )
                return notify_fail("这最后一组泥偶的招式内容过于深奥，光靠研读而不身体力行是无法再获得进步的。\n");
        me->receive_damage("jing", 20);
        me->receive_damage("neili", neili_lost);
        if (!lhlevel ) {
                write(YEL"\你专注的盯着第一组泥偶，发现其动作和姿势深得内家修行之道。\n"NOR);
                write(YEL"你定一定神，从其手势，动作姿态上观察，发现这是内家吐纳的法门。\n"NOR);
                write(YEL"于是你开始按照泥偶的姿势，打坐运气。\n\n"NOR);
        }
        if (lhlevel >= 140)
                write("你仔细观察照泥偶的姿势，再对照之前通过泥偶研习的运气法门，这才有点心得。\n");
        else
                write("你研习「十八泥偶」，颇有心得。\n");
        me->improve_skill("luohan-fumogong", me->query_skill("force", 1));
        if (!random(9)) message("vision", me->name() + "拿着一组十八泥偶仔细钻研。\n", environment(me), ({me}));
        if (me->query_skill("luohan-fumogong", 1) > lhlevel) {
                if (lhlevel == 29) {
                        write(YEL"\n你研习完了第一组泥偶，觉得这组泥偶讲的是入门基础虽然比较容易，但大有奥妙之处。\n"NOR);
                        write(YEL"你开始研习第二组泥偶，上面讲述的是练气、打坐的法门。\n\n"NOR);
                }
                else if (lhlevel == 69) {
                        write(YEL"\n你研习完了第二组泥偶，虽然这组罗汉所表现的是练气、打坐的法门，但你觉得这罗汉伏魔功实在是威力无穷。\n"NOR);
                        write(YEL"你开始研习第三组泥偶，这组泥偶所表现的是运气诀要。\n\n"NOR);
                }
                else if (lhlevel == 139) {
                        write(YEL"\n你研习完了第三组泥偶，此运气诀要颇为艰深，你费了好大的劲才完全理解了。\n"NOR);
                        write(HBYEL HIR"偶然间你用力一撮，泥人的外层全部碎开，你骇然发现原来这些泥人居然有两层，内层泥人身上同样有着一道道的经络图。\n\n"NOR);
                        write(HBYEL HIR"你仔细观察着所有被脱了“外套”的泥人，上面所标记的经络图记载着一门十分高深的内功心法，于是你赶紧对照着修炼起来。\n\n"NOR);
                         
                }
                else if (lhlevel == 221) {
                        write(HBMAG HIY"\n你终于研习完了所有的泥偶，微微一运气，就感觉到内力澎湃，源源不绝。\n"NOR);
                       
                }
        }
        if( !me->query("quest/摩天崖/luohan")){
		me->set("quest/摩天崖/luohan", 1);
		log_file("quest/摩天崖/luohan",sprintf("%8s%-10s成功得到并开始研读罗汉伏魔功，此时等级是：%s。\n",
			me->name(1),"("+capitalize(me->query("id"))+")", chinese_number(lhlevel )), me);
        }
        return 1;
}
