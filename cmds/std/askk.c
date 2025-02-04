// ask.c
// From ES2
// Modified by Xiang for XKX (12/15/95)
//修改部分不规范的代码以便message.c正确判断屏蔽信息。by Jpei 2010

#include <ansi.h>
string query_inquiry(object ob);
inherit F_CLEAN_UP;

string *msg_dunno = ({
        "$n摇摇头，说道：没听说过。\n",
        "$n疑惑地看着$N，摇了摇头。\n",
        "$n睁大眼睛望着$N，显然不知道$P在说什么。\n",
        "$n耸了耸肩，很抱歉地说：无可奉告。\n",
        "$n说道：嗯....这我可不清楚，你最好问问别人吧。\n",
        "$n想了一会儿，说道：对不起，你问的事我实在没有印象。\n",
});

int main(object me, string arg)
{
        string dest, topic, msg;
        object ob;
        //mapping inquiry;
        string str;


        seteuid(getuid());
                        str=read_file("/log/NEWS");

        if( me->is_busy() )
                return notify_fail("您先歇口气再说话吧。\n");

        if( !arg || sscanf(arg, "%s about %s", dest, topic)!=2 )
                return notify_fail("你要问谁什么事？\n");

        if( !objectp(ob = present(dest, environment(me))) )
                return notify_fail("这里没有这个人。\n");

        if( !ob->is_character() ) {
                message_vision("$N对着$n自言自语....\n", me, ob);
                return 1;
        }

        if( !ob->query("can_speak") ) {
//增加ask内容颜色醒目reikou 20071015
                message_vision("$N向$n打听有关『" + HIG +topic + NOR + "』的消息，但是$p显然听不懂人话。\n", me, ob);
                return 1;
        }

        if( !INQUIRY_D->parse_inquiry(me, ob, topic) )
                message_vision("$N向$n打听有关『" + HIG +topic + NOR + "』的消息。\n", me, ob);

        if( userp(ob) ) return 1;
        if( !living(ob) ) {
                message_vision("但是很显然的，$n现在的状况没有办法给$N任何答覆。\n", me, ob);
                return 1;
        }
        if(msg = ob->accept_ask(me, topic))
           { 
                  if (stringp(msg)) 
                  { 
                          message_vision(CYN "$N" CYN "对$n说道：" + msg + "\n" NOR, ob,me); 
                          return 1; 
                  } 
          }

        if( msg = ob->query("inquiry/" + topic) ) {
                if( stringp(msg) ) {
                         message_vision(CYN "$N" CYN "对$n说道：" + msg + "\n" NOR, ob,me); 
                        return 1;
                }
        } else {
                if(ob->query("race")=="野兽") {
                        message_vision("但是很显然的，$n根本听不懂$N的话。\n",NOR, me,ob);
                        return 1;
                }
                switch(topic) {
                        case "name":
                        message_vision( CYN "$N对$n说道：我的名字就是$N," + RANK_D->query_respect(me)+ "有什么事?\n" NOR, ob,me);
                                break;
                        case "here":
                                message_vision(CYN "$n对$N说道：这里是" + environment(ob)->query("short") + "，其它情况" + 

RANK_D->query_self(ob) + "也不太清楚。\n" NOR, me, ob);
                                break;
                        default:
                if(topic=="news")
                        {
                        if (!str)
                        {
                        message_vision( CYN "$N对$n说到,最近没什么新闻可说..\n" NOR, ob, me);
                        }
else {
                        message_vision( CYN "$N对$n说到,最近听有人说过:"+str+"" NOR, ob, me);
}
                        return 1;
                }       
                if(topic=="all")
                        {
                        message_vision( CYN "$N对$n悄声说道:"+query_inquiry(ob)+"!\n" NOR, ob,me);
                        return 1;
                }
                                if (topic == ob->query("name") || ob->id(topic))
                                message_vision(CYN "$n说道：那就是" + RANK_D->query_self_rude(ob) + "呀。\n" NOR, me, ob);
                                else if (topic == me->query("name") || me->id(topic))
                                message_vision(CYN "$n说道：那就是" + RANK_D->query_rude(me) + "你呀。\n" NOR, me, ob);
                                else if (topic == ob->query("name") || ob->id(topic))
                                EMOTE_D->do_emote(ob, "name1");
else
                                        message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
                }
        }
		me->add_busy(1);
        return 1;
}

string query_inquiry(object ob)
{
        int i=0;
        mapping inq;
        string str="", *indexs;
        
        if(mapp(inq=ob->query("inquiry")))
                {
                indexs=keys(inq);
                for(i=0;i<sizeof(indexs);i++)
                        {
                                str=indexs[i]+" "+str;
                                }
                str="有关于 "HIB+str+NOR CYN"的事情,我很高兴告诉你!";
                return str;
                }
        return "实在是对不起,我什么也不知道呀!";
        }

int help(object me)
{
   write( @HELP
指令格式: askk <someone> about <something>

这个指令在解谜时很重要, 通常必须藉由此一指令才能
获得进一步的资讯。
预设的询问主题:
        here
        name
        news
        all
HELP
   );
   return 1;
}


