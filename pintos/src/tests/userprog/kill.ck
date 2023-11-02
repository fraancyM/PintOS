# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(kill) begin
(kill) Sto eseguendo la chiamata a kill()...
kill: exit(-1)
EOF
pass "kill eseguita correttamente!"
