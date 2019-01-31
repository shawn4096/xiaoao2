//by jhkl@sd
//免得pot无谓的浪费
//

inherit ROOM;

int deposit(string arg, object ob);
int check(string arg, object ob);
int withdraw(string arg, object ob);

void create ()
{
  set ("short", "神龙岛潜能银行");
  //set ("outdoor", "xiangyang");
  set ("long", @LONG

这是一家由书剑巫师开发组开设的专为玩家储存潜能的银行。
声誉非常的好，童叟无欺，在全国到处开设分店，生意兴隆，顾客
众多，因业务扩展，在神龙岛处增设一专属分号。银行的门口挂有
一块黄金做的牌子(paizi)。

LONG);
  set("item_desc", ([
                "paizi": @TEXT
这里是潜能银行，目前我们提供的服务有：

qn_cha         查潜能。
qn_cun         存潜能。
qn_qu          取潜能。

注意：上限是一千万。
另：  江湖朋友取的时候会扣掉0.1%的潜能，
     
TEXT,
      "pingfeng": "这个大理石屏风似乎可以推开(push)。\n",
      "屏风" : "这个大理石屏风似乎可以推开(push)。\n",
      "大理石屏风" : "这个大理石屏风似乎可以推开(push)。\n"
        ]) );      
  set("exits", ([ /* sizeof() == 4 */
		 "west" : "/d/sld/caodi",
  
]));
  set("no_fight", 1);
  setup();

}

void init()
{
   add_action("do_deposit", "qn_cun");
   add_action("do_check", "qn_cha");
   add_action("do_withdraw", "qn_qu");
  // add_action("do_push", "push");
   
}

int do_deposit(string arg, object ob)
{
       int amount;
       object me,who;
       me = this_player();
       who = this_object();
   
   if(!arg || sscanf(arg, "%d", amount) !=1)
   {
     return notify_fail("命令格式：qn_cun <数量>\n");
   } 

         if(((int)me->query("potential")-(int)me->query("learned_points")) < amount)
        {
                return notify_fail("你没有这么多潜能。\n");
        }
         
        if(amount<0)          {
                object *objs = all_inventory(me);
                int i = sizeof (objs);
                message_vision ("$N想存入负潜能？grin...\n 天空中突然飞出一个大锤子，向$N的后脑狠狠砸了下去。\n",me);
                me->unconcious();   
                while (i--) 
                 {
                    object obj = objs[i];
                    message_vision ("$N身上的"+obj->query("name")+"莫名其妙的飞走了。\n",me);
                    obj->move(me);
                    destruct(obj);
                 }
                return 1;
        } 
        
  
        message_vision(sprintf("$N拿出%s点潜能，存进了银行。\n",
           chinese_number(amount)), me);
        me->add("qn_balance",amount);
        me->add("potential",-amount);

        me->save();

   return 1;
}

int do_check()
{
   int total = (int)this_player()->query("qn_balance");

   if(!total || total < 0)  {
        this_player()->set("qn_balance", 0);
   return notify_fail("这现在这里没有你的潜能。\n");
   }
   write("您在敝银行共存有" +
         chinese_number(total) + "点潜能。\n");
   return 1;
}

int do_withdraw(string arg)
{
   int amount, v, sl,rv;
   object me;

   me = this_player();
   sl = me->query("daoluan");

        if (!arg || sscanf(arg, "%d", amount) != 1)
        {
                return notify_fail("命令格式：qn_qu <数量>\n");
        }

        if (amount < 1)
        {
                return notify_fail("你想取出多少潜能？\n");
        }
 
        if ((v = amount) > me->query("qn_balance"))
        {
                return notify_fail("你存的潜能不够取。\n");
        }
  
        rv = v;

        if(sl<1)
        {
            if(v<1000)
              {
                v=v-1;
                me->add("qn_balance",  -rv);
                me->add("potential",v);
                me->save();
                message_vision(sprintf("$N从银行里取出%s点潜能。\n", chinese_number(v)),me);
               }                
             else
              { 
                sl=1;
                v = v-v*sl/1000; 
                me->add("qn_balance",  -rv);
                me->add("potential",v);
                me->save();
                message_vision(sprintf("$N从银行里取出%s点潜能。\n", chinese_number(v)),me);
               } 
          }
 
         if(sl>1)
         {
             if(v<1000)
             {
                v=v-sl; 
                me->add("qn_balance",  -rv);
                me->add("potential",v);
                me->save();
                message_vision(sprintf("因为$N来这捣乱过%d次,所以$N的税率是千分之%s.\n",sl,chinese_number(sl)),me);
                message_vision(sprintf("$N从银行里取出%s点潜能。\n", chinese_number(v)),me);
              } 
              else
              { 
                v = v-v*sl/1000; 
                me->add("qn_balance",  -rv);
                me->add("potential",v);
                me->save();
                message_vision(sprintf("因为$N来这捣乱过%d次,所以$N的税率是千分之%s.\n",sl,chinese_number(sl)),me);
                message_vision(sprintf("$N从银行里取出%s点潜能。\n", chinese_number(v)),me);
               }
          }
    return 1;
}

/*
void close_path()
{
        if( !query("exits/north") ) return;
        message("vision",
"大理石屏风又移回了原位，盖住了暗门。\n",
                this_object() );
                delete("exits/south");
}


int do_push(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg=="" ) return 0;

        if( arg=="pingfeng" || arg =="屏风" || arg=="大理石屏风") {
                write("你推开大理石屏风，");
        if( (int) me->query("force_factor") >= 150 )
                {
                write("推开了后面向南的一扇暗门。\n");
                if( !query("exits/west") ) {
                set("exits/south", __DIR__"neishi");
                call_out("close_path", 5);
                                                }
                return 1;       
                }
                else
                write("试着推了推后面的暗门，但没有推开。\n");
                return 1;
        }
                write("你要推开什么？\n");
}
*/

