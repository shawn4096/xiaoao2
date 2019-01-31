//by jhkl@sd
//免得pot无谓的浪费
//

inherit ROOM;

int deposit(string arg, object ob);
int check(string arg, object ob);
int withdraw(string arg, object ob);

void create ()
{
  set ("short", "潜能银行西域分号");
  set ("long", @LONG

潜能银行在西域所开分号，柜台上有金色小牌(paizi)，
言道此物有存取潜能之功用。

LONG);
  set("item_desc", ([
                "paizi": @TEXT
这里是潜能银行ATM，目前我们提供的服务有：

qn_cha         查潜能。
qn_cun         存潜能。
qn_qu          取潜能。

注意：上限是一千万。
另：  江湖朋友取的时候会扣掉0.1%的潜能，
     
TEXT,
        ]) );      
  set("exits", ([ /* sizeof() == 4 */
  "up" : "/d/xingxiu/silk",
  
]));
  set("no_fight", 1);
  setup();

}

void init()
{
   add_action("do_deposit", "qn_cun");
   add_action("do_check", "qn_cha");
   add_action("do_withdraw", "qn_qu");
  
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
