#!/bin/bash
# Yang  when and must conditional xpath specification
# Testing of validation phase.

APPNAME=example
# include err() and new() functions and creates $dir
. ./lib.sh

cfg=$dir/conf_yang.xml
fyang=$dir/test.yang

cat <<EOF > $cfg
<config>
  <CLICON_CONFIGFILE>$cfg</CLICON_CONFIGFILE>
  <CLICON_YANG_DIR>/usr/local/share/$APPNAME/yang</CLICON_YANG_DIR>
  <CLICON_YANG_MODULE_MAIN>$APPNAME</CLICON_YANG_MODULE_MAIN>
  <CLICON_CLISPEC_DIR>/usr/local/lib/$APPNAME/clispec</CLICON_CLISPEC_DIR>
  <CLICON_CLI_DIR>/usr/local/lib/$APPNAME/cli</CLICON_CLI_DIR>
  <CLICON_CLI_MODE>$APPNAME</CLICON_CLI_MODE>
  <CLICON_SOCK>/usr/local/var/$APPNAME/$APPNAME.sock</CLICON_SOCK>
  <CLICON_BACKEND_PIDFILE>/usr/local/var/$APPNAME/$APPNAME.pidfile</CLICON_BACKEND_PIDFILE>
  <CLICON_CLI_GENMODEL_COMPLETION>1</CLICON_CLI_GENMODEL_COMPLETION>
  <CLICON_XMLDB_DIR>/usr/local/var/$APPNAME</CLICON_XMLDB_DIR>
  <CLICON_XMLDB_PLUGIN>/usr/local/lib/xmldb/text.so</CLICON_XMLDB_PLUGIN>
</config>
EOF

cat <<EOF > $fyang
module $APPNAME{
  prefix ex;
  identity routing-protocol {
     description
        "Base identity from which routing protocol identities are
         derived.";
  }
  identity direct {
       base routing-protocol;
       description
         "Routing pseudo-protocol which provides routes to directly
          connected networks.";
  }
  identity static {
       base routing-protocol;
       description
         "Static routing pseudo-protocol.";
  }
  list whenex {
     key "type name";
     leaf type {
        type identityref {
           base routing-protocol;
        }
     }
     leaf name {
        type string;
     }
     leaf route-preference {
        type uint32;
     }
     container static-routes {
         when "../type='static'" {
            description
               "This container is only valid for the 'static'
                routing protocol.";
         }
         presence true;
     }
  }
  container interface {
     leaf ifType {
        type enumeration {
           enum ethernet;
           enum atm;
        }
     }
     leaf ifMTU {
        type uint32;
     }
     must 'ifType != "ethernet" or ifMTU = 1500' {
        error-message "An Ethernet MTU must be 1500";
     }
     must 'ifType != "atm" or'
          + ' (ifMTU <= 17966 and ifMTU >= 64)' {
        error-message "An ATM MTU must be 64 .. 17966";
     }
  }
}
EOF

# kill old backend (if any)
new "kill old backend"
sudo clixon_backend -zf $cfg -y $fyang
if [ $? -ne 0 ]; then
    err
fi

new "start backend -s init -f $cfg -y $fyang"
# start new backend
sudo $clixon_backend -s init -f $cfg -y $fyang
if [ $? -ne 0 ]; then
    err
fi

new "when: add static route"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><edit-config><target><candidate/></target><config><whenex><type>static</type><name>r1</name><static-routes/></whenex></config></edit-config></rpc>]]>]]>" "^<rpc-reply><ok/></rpc-reply>]]>]]>$"

new "when: validate ok"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><validate><source><candidate/></source></validate></rpc>]]>]]>" "^<rpc-reply><ok/></rpc-reply>]]>]]>$"

new "when: add direct route"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><edit-config><target><candidate/></target><config><whenex><type>direct</type><name>r2</name><static-routes/></whenex></config></edit-config></rpc>]]>]]>" "^<rpc-reply><ok/></rpc-reply>]]>]]>$"

new "when get config"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><get-config><source><candidate/></source></get-config></rpc>]]>]]>" "^<rpc-reply><data><whenex><type>direct</type><name>r2</name><static-routes/></whenex><whenex><type>static</type><name>r1</name><static-routes/></whenex></data></rpc-reply>]]>]]>$"

new "when: validate fail"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><validate><source><candidate/></source></validate></rpc>]]>]]>" "^<rpc-reply><rpc-error><error-tag>operation-failed</error-tag><error-type>application</error-type><error-severity>error</error-severity><error-message>xpath static-routes validation failed</error-message></rpc-error></rpc-reply>]]>]]>$"

new "when: discard-changes"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><discard-changes/></rpc>]]>]]>" "^<rpc-reply><ok/></rpc-reply>]]>]]>$"

new "must: add interface"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><edit-config><target><candidate/></target><config><interface><ifType>ethernet</ifType><ifMTU>1500</ifMTU></interface></config></edit-config></rpc>]]>]]>" "^<rpc-reply><ok/></rpc-reply>]]>]]>$"

new "must: validate ok"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><validate><source><candidate/></source></validate></rpc>]]>]]>" "^<rpc-reply><ok/></rpc-reply>]]>]]>$"

new "must: add atm interface"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><edit-config><target><candidate/></target><config><interface><ifType>atm</ifType><ifMTU>32</ifMTU></interface></config></edit-config></rpc>]]>]]>" "^<rpc-reply><ok/></rpc-reply>]]>]]>$"

new "must: atm validate fail"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><validate><source><candidate/></source></validate></rpc>]]>]]>" "^<rpc-reply><rpc-error><error-tag>operation-failed</error-tag><error-type>application</error-type><error-severity>error</error-severity><error-message>An ATM MTU must be 64 .. 17966</error-message></rpc-error></rpc-reply>]]>]]>$"

new "must: add eth interface"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><edit-config><target><candidate/></target><config><interface><ifType>ethernet</ifType><ifMTU>989</ifMTU></interface></config></edit-config></rpc>]]>]]>" "^<rpc-reply><ok/></rpc-reply>]]>]]>$"

new "must: eth validate fail"
expecteof "$clixon_netconf -qf $cfg -y $fyang" 0 "<rpc><validate><source><candidate/></source></validate></rpc>]]>]]>" "^<rpc-reply><rpc-error><error-tag>operation-failed</error-tag><error-type>application</error-type><error-severity>error</error-severity><error-message>An Ethernet MTU must be 1500</error-message></rpc-error></rpc-reply>]]>]]>"

new "Kill backend"
# Check if premature kill
pid=`pgrep -u root -f clixon_backend`
if [ -z "$pid" ]; then
    err "backend already dead"
fi
# kill backend
sudo clixon_backend -z -f $cfg
if [ $? -ne 0 ]; then
    err "kill backend"
fi

rm -rf $dir
