_paf()
{
    local cur prev opts base
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    
    # Basic options
    _paf_commands="-h --help createselector inspecttree reset"

    # Completion of basic arbuments
    case "${prev}" in
	reset)
	    local opts="-a -h --help"
	    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
            return 0
            ;;
	createselector)
	    local opts="-h --help"
	    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
            return 0
            ;;
	inspecttree)
	    local rootfiles=$( ls *.root 2> /dev/null )
	    local opts="-h -b -t -s --help --branch --tree --snippet $rootfiles"
	    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
            return 0
            ;;
	*)
	    ;;
    esac

    COMPREPLY=( $(compgen -W "${_paf_commands}" -- ${cur}) )
    return 0
  
}

complete -F _paf paf