<?php

/**
 * @file xero-creditnote.tpl.php
 * 
 * Available variables:
 * - $creditnote: the raw array structure for a credit note
 * - $currency: the currency code used for this credit note (e.g.: USD).
 * - $type: the type of credit note: accrec or accpay.
 * - $status: the status of the credit note: drafted, submitted, accepted, etc...
 * - $creditnoteid: the raw credit note identifier.
 * - $number: the sanitized credit note number.
 * - $name: the contact name associated with the credit note
 * - $contactid: the raw contactid for this credit note.
 * - $date: the timestamp the credit note was submiitted.
 * - $duedate: the timestamp the credit note is due.
 * - $paidon: optional timestamp when the credit note was paid on.
 * - $update: the timestamp when the credit note was last updated.
 * - $total: the total amount on the credit note
 * - $paid: the total amount paid on the credit note.
 * - $due: the total amount due on the credit note.
 * - $credited: the amount credited.
 * - $lineamounttypes: the line amount type
 * - $lineitems: an array of line items to be themed
 *
 * @see template_preprocess_xero_credit note().
 */
?>
<div class="xero-creditnote xero-creditnote-<?php print $type; ?>">
  <h2 class="title"><?php print $number; ?></h2>

  <div class="submitted">
    <span class="date">Submitted on <?php print format_date($date, 'short'); ?></span><br />
    <span class="date">Due on <?php print format_date($duedate, 'short'); ?></span><br />
    <?php if ($paidon <> '') : ?>
    <span class="date">Paid on <?php print format_date($paidon, 'short'); ?></span>
    <?php endif; ?>
  </div>

  <div class="summary">
    <?php if ($currency <> '') : ?>
    <p><span class="currency">All currencies are <?php print $currency; ?></span></p>
    <?php endif; ?>
    <span class="total">Total Amount: <?php print $total; ?></span><br />
    <span class="paid">Total Paid: <?php print $paid; ?></span><br />
    <span class="due">Total Due: <?php print $due; ?></span><br />
    <span class="status">Status: <?php print $status; ?></span>
  </div>

  <?php if (!empty($lineitems)) : ?>
  <div class="line-items-wrapper">
    <?php print theme('xero_lineitems', $lineitems, $creditnote['SubTotal'], $creditnote['TotalTax'], $total); ?>
  </div>
  <?php endif; ?>

</div>
