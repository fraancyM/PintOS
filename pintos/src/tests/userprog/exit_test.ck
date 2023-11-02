# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(exit_test) begin
(exit_test) Executing 'exit_test' with exit code 20...
exit_test: exit(20)
EOF
pass "Execution of 'exit_test' complete. Exit code 20\n";
