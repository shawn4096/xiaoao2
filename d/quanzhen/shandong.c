//By Jpei 王重阳已死
//设置后山是闭关场所
//重阳真人闭关之所
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "后山山洞");
        set("long", @LONG
这里是重阳真人生前静修的山洞。阳光从洞南面照射进来，阳光
斑驳陆离，空气清新异常。洞内甚是宽阔，洞内北方放置了一个神案
案上摆放了几本道藏经典，神案后洞壁上悬挂着一副画(hua)。洞西
侧挂了一副手书介绍字迹（zi）。洞内纤尘不染，极其整洁。
LONG);
        set("exits", ([
                "out" : __DIR__"xiaolu3",
        ]));
        set("item_desc", ([
        	"hua": YEL "画中是一个中年道士的背影，看不出什么相"
                       "貌，画中道人一手指着洞西面的字迹，\n  画角题着「" HIR "活"
                       "死人像" NOR + YEL "」几个字。\n" NOR,
			"zi": HIW "题写着姬志真手书的《重阳祖师开道碑》：“ 原夫至道出自先天，太
上卓尔立其宗，累圣袭而张其后，灵源妙本，既发而不蒙，出楗玄关
大开而弗闭。从兹设教，代不乏人。然而顺世污隆，乘时步骤，去圣
愈远，灵光不属。波澜既荡，异派争流，枝叶方联而纷华竟生。散无
名之大朴，遗罔象之玄珠，忘本迷源，随声逐色。正涂壅底，道间荒
凉。由是圣人复起，究天元一气之初，洪造更新，应历数万灵之会天
挺神授而力拯颓网，祖建宗承而载维新纽、弃华摭实，授溺录迷。革
弊鼎新而玄关复启焉。重阳祖师乃其人也……。”,你仔细端详这篇字迹
似乎有点意思，但到底是什么，尚待你去研究（yanjiu）！\n" NOR,

        ]) );
        set("paper_count", 1);

        setup();
}

void init()
{
       if (this_player()->query("quest/qz/dichuan"))
	   {
		    add_action("do_ketou", "ketou");
			add_action("do_fan","fankan");
			add_action("do_canwu","canwu");
			
		}
		else {
			write(HIC"丘处机在远处喊道，后山乃祖师修炼之所，你非我大全真嫡传弟子，到处乱跑作甚？\n"NOR);
			return 0;
		}
			add_action("do_yanjiu","yanjiu");

}
int do_yanjiu(string arg)
{
	object me;
	me=this_player();
	if (!me->query_temp("qz/ketouok"))
	{
		return notify_fail("你心有所感，但研究了半天什么都没看出来！\n");
	}
	if (arg!="zi")
	{
		return notify_fail("你要揣摩研究什么？\n");
	}
			//发现金关玉锁要诀精要
	if (random(me->query("kar"))>25)
	{
			message_vision(HIY"$N根据重阳真人的提示，心有所感，从道藏经典中翻出一本薄薄的手记，上面赫然写着《金关玉锁诀精要》\n"NOR,me);
			message_vision(HIY"$N顿时心下大喜，急忙拿起要诀准备参悟（canwu）！\n"NOR,me);
			me->set_temp("qz/findyusuo",1);
	}
	write("你拿起那本金关玉锁二十四诀认真研究起来！\n");
	return 1;
}
//参悟玉锁诀
int do_canwu(string arg)
{
		int i;
        object me;
		me= this_player();
		i=me->query_int(1);
		if (me->query_skill("jinguan-yusuojue",1)>600)
			i=i/8;
		else if (me->query_skill("jinguan-yusuojue",1)>550)
			i=i/6;
		else if (me->query_skill("jinguan-yusuojue",1)>500)
			i=i/4;
		else if (me->query_skill("jinguan-yusuojue",1)>450)
			i=i/3;
		else if (me->query_skill("jinguan-yusuojue",1)>400)
			i=i/2;
		else i=i;

		if (!arg)
		{
			return notify_fail("你乱翻一通道藏经典，一无所获！\n");
		}
		if (!me->query_temp("qz/findyusuo")) {
			me->start_busy(2);
			return notify_fail("你胡乱参悟一番，心中烦躁不堪\n");
		}
		if (me->query_skill("jinguan-yusuojue",1)<200)
		{
			return notify_fail("你的金关玉锁诀不到200级，无法到此参悟心法精要！\n");
		}
		if (me->query_skill("xiantian-gong",1)<200)
		{
			return notify_fail("你的先天功不到200级，无法到此参悟心法精要！\n");
		}
		if (me->query_skill("taoism",1)<200)
		{
			return notify_fail("你的道德经不到200级，无法到此参悟心法精要！\n");
		}
		if (me->query_int()<30)
		{
			return notify_fail("你的悟性不到30，无法到此参悟心法精要！\n");
		}
		if (me->is_busy()||me->query_condition("job_busy"))
		{
			return notify_fail("你现在心烦意乱，无法到此参悟心法精要！\n");
		}
		if (arg=="金关玉锁诀"||arg=="yaojue"||arg=="jingyao")
		{
			 message_vision("当下$N盘膝而坐，仔细翻看这《金关玉锁二十四诀精要篇》。\n", me);
			//
			if((int)me->query_skill("jinguan-yusuojue", 1) > me->query("max_pot")-100 )
				return notify_fail("你受经验所限，无法再进步了。\n");
			if((int)me->query_skill("jinguan-yusuojue", 1) > me->query_skill("xiantian-gong",1) )
				return notify_fail("你受先天功所限，金关玉锁诀无法再进步了。\n");
			if((int)me->query_skill("jinguan-yusuojue", 1) > me->query_skill("xiantian-gong",1) )
				return notify_fail("你受先天功所限，金关玉锁诀无法再进步了。\n");
			
			if (me->query_skill("jinguan-yusuojue",1)>100 && !me->query("yusuo/degree"))
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第一重关口方可继续修炼。\n");
			if (me->query_skill("jinguan-yusuojue",1)>200 &&  (int)me->query("yusuo/degree")<2)
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第二重关口方可继续修炼。\n");
		
			if (me->query_skill("jinguan-yusuojue",1)>300 && (int)me->query("yusuo/degree")<3)
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第三重关口方可继续修炼。\n");
			if (me->query_skill("jinguan-yusuojue",1)>400 && (int)me->query("yusuo/degree")<4)
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第四重关口方可继续修炼。\n");
			if (me->query_skill("jinguan-yusuojue",1)>500 && me->query("yusuo/degree")<5)
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第五重关口方可继续修炼。\n");
			if (me->query_skill("jinguan-yusuojue",1)>600 && me->query("yusuo/degree")<6)
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第六重关口方可继续修炼。\n");
			if (me->query_skill("jinguan-yusuojue",1)>700 && me->query("yusuo/degree")<7)
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第七重关口方可继续修炼。\n");
			if (me->query_skill("jinguan-yusuojue",1)>800 && me->query("yusuo/degree")<8)
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第八重关口方可继续修炼。\n");
			if (me->query_skill("jinguan-yusuojue",1)>900 && me->query("yusuo/degree")<9)
				return notify_fail("你金关玉锁诀修炼到了瓶颈，需要冲破第九重关口方可继续修炼。\n");
			
			
			if (me->query("jing") < 50) {
				write("可惜你太累了，无法集中精神来研究金关玉锁二十四诀。\n");
				return 1;
			}
			if (me->query("potential")<4)
			{
				return notify_fail("你现在潜能不足,无法参悟金关玉锁二十四诀！\n");
			}
			me->add("potential",-2-random(3));
			me->receive_damage("jing", 20+random(10),"精力消耗过甚");
			if (me->query("ggs/started")&&!random(4))
			{
				i=i*2+random(i);
				tell_object(me,"你在鬼谷加持下，你的悟性大增！学起来事半功倍！\n");
			}
			me->improve_skill("jinguan-yusuojue", i);
			if (random(10)<3)
			{
				me->add_busy(1);
			}
			
			write("你如饥似渴，又掌握了一些《金关玉锁二十四诀》的技巧。\n");

		}
		return 1;


}

int do_ketou(string arg)
{
        object sword;
        object me = this_player();
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");


        if ( me->query("family/family_name")!="全真教"  ) 
                return notify_fail("你看着重阳真人的画像，想象着他傲视群雄睥睨天下的绝代风采，不由得拜了一拜。\n"); 
                
        if ( me->query("qi") <= 50)
        	      return notify_fail("就你当前身体现状还是去休息吧。"); 
        	      
     //  sword= new(BINGQI_D("sword/qixing-jian"));
		
		if (me->query_temp("quest/qz/htz/chongyang/findzi")&&arg=="青砖")
		{
			message_vision(HIW"$N不再犹豫，重重以额触地，磕在神案前中间那块青砖上。\n"NOR,me);

			message_vision(HIC"“咚咚咚”的三声重响，$N忽然意识道这地板下可能是空的，否则不会如此回响。\n"NOR,me);
			message_vision(HIY"无意中触发了机关，只听“砸砸”作响，面前显出一个入口，仅容一人进入！\n"NOR,me);
			add("exits", ([
               // "out" : __DIR__"xiaolu3",
				"rukou" : __DIR__"didao1",				
			]));
			call_out("remove_rukou",5);
			return 1;
		}
        if( me->query_temp("ketou") && arg =="画")
        {
            message_vision(HIG"$N走向前去，面对重阳祖师画像，恭恭敬敬磕头。\n"NOR,me);
            if (me->query_temp("quest/qz/htz/chongyang/askma"))
            {
	
				message_vision(HIC"$N俯身在地，眼角所视，忽然发现在神案脚腿上刻了几个小字“左数三，右数四，天地至诚，叩首三次”。\n"NOR,me);
				message_vision(HIC"$N暗自数了下青砖，发现这左三右四恰好是自己目前所面对的那块青砖！\n"NOR,me);

				me->set_temp("quest/qz/htz/chongyang/findzi",1);
            }
			
            me->set_temp("get_sword",1);
            return 1;
         }
          else
          {
             message_vision("$N恭恭敬敬地在神案前的团蒲上跪了下来，对着祖师画像磕了三个响头。\n", me);
             me->add_temp("ketou", 1);
			 if (random(me->query_temp("ketou"))>10
				 &&random(me->query("kar"))>20 )
			 {
				 message_vision(HIC"$Nn俯下身来，磕头抬头瞬间，忽然灵光乍现，重阳真人的手指方向似乎有些异常。\n"NOR, me);
				 me->set_temp("qz/ketouok",1);
			 }
             return 1;
          }
	   //磕头后会有所感悟

 }
 
int remove_rukou()
{
	
	write("一会功夫，机关扎扎作响，恢复原样，入口消失！\n");
	delete("exits/rukou");
	
	return 1;
}
//先天功quest的触发点
//触发的书也不是那么好拿的

int do_fan(string arg)
{
        object paper;
        object me = this_player();

        if (!arg || arg != "道藏经典")
                return notify_fail("你要翻什么？\n");
		
		if (me->query_skill("xiantian-gong",1)<450)
		{
			return notify_fail("你的先天功不足450，无法领悟高深功法。\n");
		}

		if (me->query_skill("quanzhen-jianfa",1)<450)
		{
			return notify_fail("你的全真剑法不足450，无法领悟高深功法。\n");
		}
		if (me->query_skill("taoism",1)<200)
		{
			return notify_fail("你的道学心法不足200，无法领悟高深功法。\n");
		}
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着哪！\n");
   
        if ( !(me->query("family/family_name")=="全真教") ) 
                return notify_fail("你随意的翻看了几页，都是玄门温养丹鼎之法，你只觉得云里雾里，不甚了解，索然无味。\n"); 
               
       if ( !me->query_temp("ketou")  ) 
                return notify_fail("你翻看了几页，都是玄门温养丹鼎之法，只觉得深奥无比。\n");        

       if ( query("paper_count") <1  ) 
                return notify_fail("你翻看了几页，都是玄门温养丹鼎之法，只觉得深奥无比。\n");        

		//发现五篇灵文

        if ( me->query_skill("xiantian-gong", 1)>=450
			 && me->query("quest/qz/xtg/dingyang/start")  //要有触发才能拿到
			 && me->query_skill("taoism", 1)>=200 
             && me->query_skill("quanzhen-jianfa", 1)>=450 
			 && random(50) >=25
			 && !me->query_temp("quanzhen/force")
             && !me->query("quanzhen/force") ) 
        {
                paper=new(__DIR__"obj/xtg_book");
                if ( !paper ) return 1;

                add("paper_count", -1);
                me->set_temp("quanzhen/force", 1);

                message_vision(HIR"$N仔细的翻看着洞中所藏道学经典，忽然间你发现其中一本中似乎夹了一小段丝绢。\n"NOR,me);
                write(MAG"你仔细的将丝绢抽出一看，上面密密麻麻的记载了练功心法，似乎与先天功一脉相承，但却更加深奥。\n"NOR);
                message_vision("$N连忙将密笈收好。\n",me);
				paper->set("owner",me->query("id"));
                paper->move(me, 1);
              return 1;
        } 
       else  
            {   me->add_temp("ketou",-1);
              message_vision("$N随意的翻看了几页，都是玄门温养丹鼎之法，你只觉得云里雾里，不甚了解，索然无味。\n",me); 
              return 1;
              }

}

