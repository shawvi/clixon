#
# ***** BEGIN LICENSE BLOCK *****
# 
# Copyright (C) 2009-2018 Olof Hagsand and Benny Holmgren
#
# This file is part of CLIXON
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Alternatively, the contents of this file may be used under the terms of
# the GNU General Public License Version 3 or later (the "GPL"),
# in which case the provisions of the GPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of the GPL, and not to allow others to
# use your version of this file under the terms of Apache License version 2, 
# indicate your decision by deleting the provisions above and replace them with
# the notice and other provisions required by the GPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the Apache License version 2 or the GPL.
#
# ***** END LICENSE BLOCK *****
#

FROM olofhagsand/clixon
MAINTAINER Olof Hagsand <olof@hagsand.se>

#RUN apt-get update && apt-get install -y procps # ps for debugging

# The example uses "clicon" group
RUN groupadd clicon

# Create a directory to hold source-code, dependencies etc
RUN mkdir /example
WORKDIR /example

# Clone clixon (again) since example application is there.
# Replace this with your application
RUN git clone https://github.com/clicon/clixon.git

# Build clixon
WORKDIR /example/clixon
RUN git checkout -b develop origin/develop
RUN ./configure
WORKDIR /example/clixon/example
RUN make
RUN make install
RUN install example.xml /usr/local/etc/clixon.xml

# Log to stderr. Add -D 1 for debug
CMD /usr/local/sbin/clixon_backend -F -a IPv4 -u 0.0.0.0 -s init -l e 





