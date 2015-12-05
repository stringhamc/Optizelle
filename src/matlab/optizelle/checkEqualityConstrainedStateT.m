% Check that we have an equality constrained state 
function checkEqualityConstrainedStateT(name,value)
    % Set the error message
    err = sprintf( ...
        'The %s argument must have type EqualityConstrained.State.t.', ...
        name);

    % Check the unconstrained values
    try
        checkUnconstrainedStateT(name,value);
    catch
        error(err);
    end

    % Check for the appropriate fields 
    if ~(checkFields({ ...
        'y', ...
        'dy', ...
        'zeta', ...
        'eta0', ...
        'rho', ...
        'rho_old', ...
        'rho_bar', ...
        'eps_constr', ...
        'xi_qn', ...
        'xi_pg', ...
        'xi_proj', ...
        'xi_tang', ...
        'xi_lmh', ...
        'xi_lmg', ...
        'xi_4', ...
        'rpred', ...
        'PSchur_left_type', ...
        'PSchur_right_type', ...
        'augsys_iter_max', ...
        'augsys_rst_freq', ...
        'augsys_qn_iter', ...
        'augsys_pg_iter', ...
        'augsys_proj_iter', ...
        'augsys_tang_iter', ...
        'augsys_lmh_iter', ...
        'augsys_qn_iter_total', ...
        'augsys_pg_iter_total', ...
        'augsys_proj_iter_total', ...
        'augsys_tang_iter_total', ...
        'augsys_lmh_iter_total', ...
        'augsys_qn_err', ...
        'augsys_pg_err', ...
        'augsys_proj_err', ...
        'augsys_tang_err', ...
        'augsys_lmh_err', ...
        'augsys_qn_err_target', ...
        'augsys_pg_err_target', ...
        'augsys_proj_err_target', ...
        'augsys_tang_err_target', ...
        'augsys_lmh_err_target', ...
        'augsys_iter_total', ...
        'g_x', ...
        'norm_gxtyp', ...
        'gpxdxn_p_gx', ...
        'gpxdxt', ...
        'norm_gpxdxnpgx', ...
        'dx_n', ...
        'dx_ncp', ...
        'dx_t', ...
        'dx_t_uncorrected', ...
        'dx_tcp_uncorrected', ...
        'H_dxn', ...
        'W_gradpHdxn', ...
        'H_dxtuncorrected', ...
        'g_diag', ...
        'y_diag', ...
        'qn_stop'}, ...
        value))
        error(err);
    end
end
