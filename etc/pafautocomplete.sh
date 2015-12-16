_paf()
{
    local cur prev opts base
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    
    # Basic options
    _paf_commands="-h --help addhistogram ah createselector cs inspecttree it reset"
    # Completion of basic arbuments
    case "${prev}" in
	reset)
	    local opts="-a -h --help"
	    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
            return 0
            ;;
	cs|createselector)
	    local opts="-h --help"
	    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
            return 0
            ;;
	it|inspecttree)
	    local IFS=$'\n'
	    local LASTCHAR=' '
	    compopt -o nospace -o filenames
	    COMPREPLY=( $(compgen -o plusdirs -f -X '!*.root' -- "${cur}") )
            return 0
            ;;
	ah|addhistogram)
	    local opts="-h --help"
	    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
	    return 0
	    ;;
	-h|--help)
	    return 0
	    ;;
	*)
	    ;;
    esac

    COMPREPLY=( $(compgen -W "${_paf_commands}" -- ${cur}) )
    return 0
  
}

complete -F _paf paf